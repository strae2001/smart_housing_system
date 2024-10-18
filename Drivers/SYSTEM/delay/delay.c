#include "delay.h"

/**
  * @brief  ΢�뼶��ʱ
  * @param  nus ��ʱʱ������Χ��0~233015
  * @retval ��
  */
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t tcnt = 0, told, tnow;
    uint32_t reload = SysTick->LOAD;                //��װ��ֵ
    
    ticks = nus * 72;                               //��Ҫ�ƵĽ�����
    told = SysTick->VAL;                            //�ս���whileѭ��ʱ��������ֵ
    
    while(1)
    {
        tnow = SysTick->VAL;
        if(tnow != told)
        {
            if(tnow < told)
                tcnt += told - tnow;
            else
                tcnt += reload - (tnow -told);
            
            told = tnow;                            //�´ν���whileѭ��ʱ����ǰVAL��ֵ��Ϊtold
            
            if(tcnt >= ticks)                       //�ѼƵ�������/������Ҫ�Ƶ���ʱ���˳�ѭ��
                break;
        }
    }
}

/**
  * @brief  ���뼶��ʱ
  * @param  nms ��ʱʱ������Χ��0~4294967295
  * @retval ��
  */
void delay_ms(uint32_t nms)
{
    while(nms--)
        delay_us(1000);
}
 
/**
  * @brief  �뼶��ʱ
  * @param  ns ��ʱʱ������Χ��0~4294967295
  * @retval ��
  */
void delay_s(uint32_t ns)
{
    while(ns--)
        delay_ms(1000);
}

/**
  * @brief  ��дHAL_Delay����
  * @param  nms ��ʱʱ������Χ��0~4294967295
  * @retval ��
  */
void HAL_Delay(uint32_t nms)
{
    delay_ms(nms);
}
