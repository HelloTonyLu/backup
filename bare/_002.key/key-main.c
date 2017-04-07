/* 1��LED�ƽӿ����üĴ��� */
#define GPM4CON (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT (*(volatile unsigned int *)0x110002E4)

/* 2�������ӿ����üĴ��� */
#define GPX3CON (*(volatile unsigned int *)0x11000C60)
#define GPX3DAT (*(volatile unsigned int *)0x11000C64)

/* 3���������ӿ�����*/
#define GPD0CON (*(volatile unsigned int *)0x114000A0)
#define GPD0DAT (*(volatile unsigned int *)0x114000A4)

int main(void)
{
        /* 1������GPM4CONΪ���ģʽ */
        GPM4CON &= ~((0xf << 3 * 4) | (0xf << 2 * 4) | (0xf << 1 * 4) | (0xf << 0 * 4));
        GPM4CON |=  ((1  << 3 * 4) | (1  << 2 * 4) | (1  << 1 * 4) | (1  << 0 * 4));

        /* 2�����ð����ӿڹܽ�Ϊ����ģʽ
         * key1 ---> GPX3_2
         * key2 ---> GPX3_3
         * key3 ---> GPX3_4
         * key4 ---> GPX3_5
         */
        GPX3CON &= ~((0xf << 2 * 4) | (0xf << 3 * 4) | (0xf << 4 * 4) | (0xf << 5 * 4));
        
        /* 3. ���÷�����Ϊ���ģʽ */
        GPD0CON &= ~(0xf << 0 * 4);
        GPD0CON |=  (1   << 0 * 4);
    
        /* 4������key������led�� */
        while(1) 
        {
                if(!(GPX3DAT & (1 << 2)))       // �жϰ���1�Ƿ��£�������½���if���
                {  
                        GPM4DAT &= ~(1 << 0);   // ������һ����
                        GPD0DAT |= (1 << 0);    // ��������
                }

                else if(!(GPX3DAT & (1 << 3)))  // �жϰ���2�Ƿ��£�������½���if���
                {
                        GPM4DAT &= ~(1 << 1);   // �����ڶ�����
                GPD0DAT |= (1 << 0);            // ��������
                }

                else if(!(GPX3DAT & (1 << 4)))  // �жϰ���3�Ƿ��£�������½���if���
                {
                        GPM4DAT &= ~(1 << 2);   // ������������
                        GPD0DAT |= (1 << 0);    // ��������
                }

                else if(!(GPX3DAT & (1 << 5)))  // �жϰ���4�Ƿ��£�������½���if���
                { 
                        GPM4DAT &= ~(1 << 3);   // �������ĸ���
                        GPD0DAT |= (1 << 0);    // ��������
                }

                else
                {
                        // ���û�а�������ȫ��
                        GPM4DAT |= (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
                        GPD0DAT &=~(1 << 0);    // �ط�����
                }
        }
        return 0;
}

