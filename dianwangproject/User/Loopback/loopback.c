#include <stdio.h>
#include "loopback.h"
#include "socket.h"
#include "wizchip_conf.h"
#include "usart.h"

#if LOOPBACK_MODE == LOOPBACK_MAIN_NOBLCOK

extern uint16_t tcp_len; 
extern uint8_t  TCP_Recved;       //接收状态标记



#define DATA_BUF_SIZE 2048
#define KEEPALIVE_IDLE_TIME 60  // 60秒keepalive空闲时间
#define MAX_RETRIES 3           // 最大重试次数

void do_tcp_server(uint8_t sn, uint8_t *buf, uint16_t port)
{	
	uint16_t len=0;  
	switch(getSn_SR(sn))											            	/*获取socket的状态*/
	{
		case SOCK_CLOSED:													                  /*socket处于关闭状态*/
			socket(sn ,Sn_MR_TCP,port,Sn_MR_ND);	        /*打开socket*/
		  break;     
    
		case SOCK_INIT:														                  /*socket已初始化状态*/
			listen(sn);												                /*socket建立监听*/
		  break;
		
		case SOCK_ESTABLISHED:												              /*socket处于连接建立状态*/
		
			if(getSn_IR(sn) & Sn_IR_CON)
			{
				setSn_IR(sn, Sn_IR_CON);								          /*清除接收中断标志位*/
			}
			len=getSn_RX_RSR(sn);									            /*定义len为已接收数据的长度*/
			if(len>0)
			{
				recv(sn,buf,len);								              	/*接收来自Client的数据*/
				if(len < sizeof(buf)) 
					buf[len]=0x00; 											                  /*添加字符串结束符*/
				//printf("%s\r\n",buf);
				//send(sn,buf,len);									              /*向Client发送数据*/
				 parseTCPCmd(buf,len);
		  }
		  break;
		
		case SOCK_CLOSE_WAIT:												                /*socket处于等待关闭状态*/
			close(sn);
		  break;
	}
}


int32_t loopback_mytcps(uint8_t sn, uint8_t *buf, uint16_t port) {
    int32_t ret;
    uint16_t size = 0, sentsize = 0;
    static uint8_t retry_count = 0;

    switch(getSn_SR(sn)) {
    case SOCK_INIT:
        if(listen(sn) != SOCK_OK) {
            close(sn);
            return -1;
        }
        // 设置socket选项
        setSn_KPALVTR(sn, KEEPALIVE_IDLE_TIME); // 配置keepalive
        //setSn_MR(sn, Sn_MR_TCP | Sn_MR_MF);     // 启用MAC过滤
        break;

    case SOCK_ESTABLISHED:
        if(getSn_IR(sn) & Sn_IR_CON) {
            setSn_IR(sn, Sn_IR_CON); // 清除连接中断标志
            retry_count = 0;         // 重置重试计数器
        }

        if((size = getSn_RX_RSR(sn)) > 0) {
            if(size > DATA_BUF_SIZE) 
							size = DATA_BUF_SIZE;
            
            // 带重试机制的接收
            for(int i=0; i<MAX_RETRIES; i++) {
                ret = recv(sn, buf, size);
                if(ret > 0) break;
                if(ret == SOCKERR_TIMEOUT) continue;
                close(sn);
                return ret;
            }

            size = (uint16_t)ret;
            if(size == 0) { // 对端关闭连接
                disconnect(sn);
                break;
            }

            // 数据处理
            //buf[size] = 0x00;
           // parseTCPCmd(buf, size);
        
        }
        break;

    case SOCK_CLOSE_WAIT:
        // 完整四次挥手流程
        if((ret = disconnect(sn)) == SOCK_OK) {
            HAL_Delay(200); // 等待2MSL时间
            socket(sn, Sn_MR_TCP, port, 0); // 重新初始化socket
        }
        break;

    case SOCK_CLOSED:
        // 带延迟的自动重连
        HAL_Delay(1000);
        socket(sn, Sn_MR_TCP, port, 0);
        break;

    default:
        // 处理其他异常状态
        close(sn);
        socket(sn, Sn_MR_TCP, port, 0);
        break;
    }
    return 0;
}


/**
 * @brief   tcp server loopback test
 * @param   sn:    socket number
 * @param   buf:   Data sending and receiving cache
 * @param   port:  Listen port
 * @return  value for SOCK_ERRORs,return 1:no error
 */
int32_t loopback_tcps(uint8_t sn, uint8_t *buf, uint16_t port)
{
   int32_t ret;
   uint16_t size = 0, sentsize = 0;

#ifdef _LOOPBACK_DEBUG_
   uint8_t destip[4];
   uint16_t destport;
#endif

   switch (getSn_SR(sn))
   {
		 case SOCK_ESTABLISHED:
      if (getSn_IR(sn) & Sn_IR_CON)
      {
#ifdef _LOOPBACK_DEBUG_
         getSn_DIPR(sn, destip);
         destport = getSn_DPORT(sn);

        // printf("%d:Connected - %d.%d.%d.%d : %d\r\n", sn, destip[0], destip[1], destip[2], destip[3], destport);
#endif
         // We need to send a packet of data to activate keepalive
//         ret = send(sn, (uint8_t *)"", 1); // Data send process
//         if (ret < 0)                      // Send Error occurred (sent data length < 0)
//         {
//            close(sn); // socket close
//            return ret;
//         }
         setSn_IR(sn, Sn_IR_CON);
      }
      if ((size = getSn_RX_RSR(sn)) > 0) // Don't need to check SOCKERR_BUSY because it doesn't not occur.
      {
         if (size > DATA_BUF_SIZE)
            size = DATA_BUF_SIZE;
         ret = recv(sn, buf, size);

         if (ret <= 0)
            return ret; // check SOCKERR_BUSY & SOCKERR_XXX. For showing the occurrence of SOCKERR_BUSY.
         size = (uint16_t)ret;
         sentsize = 0;
         buf[size] = 0x00;
////////////////////解析数据///////////////////////////////////////
				 
				 parseTCPCmd(buf,size);
				 
///////////////////////////////////////////////////////////////////
        // printf("rece data:%s\r\n", buf);
//         while (size != sentsize)
//         {
//            ret = send(sn, buf + sentsize, size - sentsize);
//            if (ret < 0)
//            {
//               close(sn);
//               return ret;
//            }
//            sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
//         }
				 //////////////////////////////////
      }
      break;
   case SOCK_CLOSE_WAIT:
#ifdef _LOOPBACK_DEBUG_
      printf("%d:CloseWait\r\n", sn);
#endif
      if ((ret = disconnect(sn)) != SOCK_OK)
         return ret;
			close(sn);
			socket(sn, Sn_MR_TCP, port, 0x00); // 重新初始化
#ifdef _LOOPBACK_DEBUG_
      printf("%d:Socket Closed\r\n", sn);
#endif
      break;
   case SOCK_INIT:
#ifdef _LOOPBACK_DEBUG_
      printf("%d:Listen, TCP server loopback, port [%d]\r\n", sn, port);
#endif
      if ((ret = listen(sn)) != SOCK_OK)
         return ret;
      break;
   case SOCK_CLOSED:
#ifdef _LOOPBACK_DEBUG_
      printf("%d:TCP server loopback start\r\n", sn);
#endif
      if ((ret = socket(sn, Sn_MR_TCP, port, 0x00)) != sn)
         return ret;
#ifdef _LOOPBACK_DEBUG_
      printf("%d:Socket opened\r\n", sn);
#endif
      break;
   default:
      break;
   }
   return 1;
}

/**
 * @brief   tcp client loopback test
 * @param   sn:         socket number
 * @param   buf:        Data sending and receiving cache
 * @param   destip:     Destination IP address
 * @param   destport:   Destination port
 * @return  value for SOCK_ERRORs,return 1:no error
 */
int32_t loopback_tcpc(uint8_t sn, uint8_t *buf, uint8_t *destip, uint16_t destport)
{
   int32_t ret; // return value for SOCK_ERRORs
   uint16_t size = 0, sentsize = 0;

   // Destination (TCP Server) IP info (will be connected)
   // >> loopback_tcpc() function parameter
   // >> Ex)
   uint8_t dip[4] = {192, 168, 0, 214};
   uint16_t dport = 5000;
   getSn_DIPR(sn, dip);
   dport = getSn_DPORT(sn);
   // Port number for TCP client (will be increased)
   static uint16_t any_port = 50000;

   // Socket Status Transitions
   // Check the W5500 Socket n status register (Sn_SR, The 'Sn_SR' controlled by Sn_CR command or Packet send/recv status)
   switch (getSn_SR(sn))
   {
   case SOCK_ESTABLISHED:
      if (getSn_IR(sn) & Sn_IR_CON) // Socket n interrupt register mask; TCP CON interrupt = connection with peer is successful
      {
         // We need to send a packet of data to activate keepalive
         ret = send(sn, (uint8_t *)"", 1); // Data send process
         if (ret < 0)                      // Send Error occurred (sent data length < 0)
         {
            close(sn); // socket close
            return ret;
         }
#ifdef _LOOPBACK_DEBUG_
         printf("%d:Connected to - %d.%d.%d.%d : %d\r\n", sn, destip[0], destip[1], destip[2], destip[3], destport);
#endif
         setSn_IR(sn, Sn_IR_CON); // this interrupt should be write the bit cleared to '1'
      }

      //////////////////////////////////////////////////////////////////////////////////////////////
      // Data Transaction Parts; Handle the [data receive and send] process
      //////////////////////////////////////////////////////////////////////////////////////////////
      if ((size = getSn_RX_RSR(sn)) > 0) // Sn_RX_RSR: Socket n Received Size Register, Receiving data length
      {
         if (size > DATA_BUF_SIZE)
            size = DATA_BUF_SIZE;   // DATA_BUF_SIZE means user defined buffer size (array)
         ret = recv(sn, buf, size); // Data Receive process (H/W Rx socket buffer -> User's buffer)
         buf[size] = 0x00;
         printf("rece from %d.%d.%d.%d:%d data:%s\r\n", dip[0], dip[1], dip[2], dip[3], dport, buf);
         if (ret <= 0)
            return ret; // If the received data length <= 0, receive failed and process end
         size = (uint16_t)ret;
         sentsize = 0;

         // Data sentsize control
         while (size != sentsize)
         {
            ret = send(sn, buf + sentsize, size - sentsize); // Data send process (User's buffer -> Destination through H/W Tx socket buffer)
            if (ret < 0)                                     // Send Error occurred (sent data length < 0)
            {
               close(sn); // socket close
               return ret;
            }
            sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
         }
      }
      //////////////////////////////////////////////////////////////////////////////////////////////
      break;

   case SOCK_CLOSE_WAIT:
#ifdef _LOOPBACK_DEBUG_
      printf("%d:CloseWait\r\n", sn);
#endif
      if ((ret = disconnect(sn)) != SOCK_OK)
         return ret;
#ifdef _LOOPBACK_DEBUG_
      printf("%d:Socket Closed\r\n", sn);
#endif
      break;

   case SOCK_INIT:
#ifdef _LOOPBACK_DEBUG_
      printf("%d:Try to connect to the %d.%d.%d.%d : %d\r\n", sn, destip[0], destip[1], destip[2], destip[3], destport);
#endif
      if ((ret = connect(sn, destip, destport)) != SOCK_OK)
         return ret; //	Try to TCP connect to the TCP server (destination)
      break;

   case SOCK_CLOSED:
      close(sn);
      if ((ret = socket(sn, Sn_MR_TCP, any_port++, 0x00)) != sn)
      {
         if (any_port == 0xffff)
            any_port = 50000;
         return ret; // TCP socket open with 'any_port' port number
      }
#ifdef _LOOPBACK_DEBUG_
      printf("%d:TCP client loopback start\r\n", sn);
      printf("%d:Socket opened\r\n", sn);
#endif
      break;
   default:
      break;
   }
   return 1;
}

/**
 * @brief   udp server mode loopback test
 * @param   sn:    socket number
 * @param   buf:   Data sending and receiving cache
 * @param   port:  Local port
 * @return  value for SOCK_ERRORs,return 1:no error
 */
int32_t loopback_udps(uint8_t sn, uint8_t *buf, uint16_t port)
{
   int32_t ret;
   uint16_t size, sentsize;
   uint8_t destip[4];
   uint16_t destport;

   switch (getSn_SR(sn))
   {
   case SOCK_UDP:
      if ((size = getSn_RX_RSR(sn)) > 0)
      {
         if (size > DATA_BUF_SIZE)
            size = DATA_BUF_SIZE;
         ret = recvfrom(sn, buf, size, destip, (uint16_t *)&destport);
         buf[ret] = 0x00;
         printf("recv form[%d.%d.%d.%d][%d]: %s\r\n", destip[0], destip[1], destip[2], destip[3], destport, buf);
         if (ret <= 0)
         {
#ifdef _LOOPBACK_DEBUG_
            printf("%d: recvfrom error. %ld\r\n", sn, ret);
#endif
            return ret;
         }
         size = (uint16_t)ret;
         sentsize = 0;
         while (sentsize != size)
         {
            ret = sendto(sn, buf + sentsize, size - sentsize, destip, destport);
            if (ret < 0)
            {
#ifdef _LOOPBACK_DEBUG_
               printf("%d: sendto error. %ld\r\n", sn, ret);
#endif
               return ret;
            }
            sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
         }
      }
      break;
   case SOCK_CLOSED:
#ifdef _LOOPBACK_DEBUG_
      // printf("%d:UDP loopback start\r\n",sn);
#endif
      if ((ret = socket(sn, Sn_MR_UDP, port, 0x00)) != sn)
         return ret;
#ifdef _LOOPBACK_DEBUG_
      printf("%d:Opened, UDP loopback, port [%d]\r\n", sn, port);
#endif
      break;
   default:
      break;
   }
   return 1;
}

/**
 * @brief   udp client loopback test
 * @param   sn:         socket number
 * @param   buf:        Data sending and receiving cache
 * @param   destip:     Destination IP address
 * @param   destport:   Destination port
 * @return  value for SOCK_ERRORs,return 1:no error
 */
int32_t loopback_udpc(uint8_t sn, uint8_t *buf, uint8_t *destip, uint16_t destport)
{
   int32_t ret;
   uint16_t size = 0, sentsize = 0;
   static uint16_t any_port = 50000;
   // uint8_t* strtest = "\r\nhello world";
   switch (getSn_SR(sn))
   {
   case SOCK_UDP:
      // sendto(sn, strtest, strlen(strtest), destip, destport);
      if ((size = getSn_RX_RSR(sn)) > 0)
      {
         if (size > DATA_BUF_SIZE)
            size = DATA_BUF_SIZE;
         ret = recvfrom(sn, buf, size, destip, (uint16_t *)&destport);
         buf[ret] = 0x00;
         printf("recv form[%d.%d.%d.%d][%d]: %s\r\n", destip[0], destip[1], destip[2], destip[3], destport, buf);
         if (ret <= 0)
         {
#ifdef _LOOPBACK_DEBUG_
            printf("%d: recvfrom error. %ld\r\n", sn, ret);
#endif
            return ret;
         }
         size = (uint16_t)ret;
         sentsize = 0;
         while (sentsize != size)
         {
            ret = sendto(sn, buf + sentsize, size - sentsize, destip, destport);
            if (ret < 0)
            {
#ifdef _LOOPBACK_DEBUG_
               printf("%d: sendto error. %ld\r\n", sn, ret);
#endif
               return ret;
            }
            sentsize += ret; // Don't care SOCKERR_BUSY, because it is zero.
         }
      }
      break;
   case SOCK_CLOSED:
#ifdef _LOOPBACK_DEBUG_
      // printf("%d:UDP loopback start\r\n",sn);
#endif
      if ((ret = socket(sn, Sn_MR_UDP, any_port, 0x00)) != sn)
         return ret;
#ifdef _LOOPBACK_DEBUG_
      printf("%d:Opened, UDP loopback, port [%d]\r\n", sn, any_port);
#endif
      break;
   default:
      break;
   }
   return 1;
}
#endif
