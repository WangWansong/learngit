#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>

#include "cal.h"
/******
	�ļ������� ʵϰ���׼�����
    ��Ա    ��  ������
	 ʱ�䣺		2020.9.15



*****/
static int panelHandle;
char numA[100],numB[100];					 //���������������֣��ַ�����
float numa=0.0,numb=0.0,Result=0.0;			 //�������ֺͼ�����
int numFlag=0,calFlag=0;					 //���崦�����ֵ�λ���ͼ������λ��־��1Ϊ/��2Ϊ*��3Ϊ-��4Ϊ+��
int signFlag[2]={1,1};						 //������������λ


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "cal.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

void Transform()							 //�ַ������ֺ�double����ת��
{
	numa=atof(numA); 
	numb=atof(numB); 
	if(signFlag[0]==-1)						//�����޷��������������ֺ��ַ���֮�䴫�ݣ����÷���λ������ʱ������������
	{
	  numa=-numa;	
	}
	if(signFlag[1]==-1)						//�޸�2����������
	{
	  numb=-numb;	
	} 
}
void Show()									 //��ʾ
{														//�����������
	char mit[101];
	memset(mit,0,sizeof(mit)) ; 
	strcat(mit,"-");   
	Transform();
	if(numFlag==0)										//�Ƿ�Ϊ��һ����������
	{													//�Ƿ��һ������Ϊ��
		if(signFlag[0]==1)
		{
		   SetCtrlVal(panelHandle,PANEL_STRING,numA);
		}
		else  
		{
		   strcat(mit,numA);
		   SetCtrlVal(panelHandle,PANEL_STRING,mit); 
		}
	}
	else if(numFlag==1&&calFlag!=0)					   //�ڶ�����������
	{												   //�ڶ�����������
			if(signFlag[1]==1)
			{
               SetCtrlVal(panelHandle,PANEL_STRING,numB);
			}
	      	else if(signFlag[1]==-1) 
		    {
		       strcat(mit,numB); 
	       	   SetCtrlVal(panelHandle,PANEL_STRING,mit); 
		    }
	}
 }
void Re()									 //������գ��������һ�μ����
{
     numb=0;
     calFlag=0;
     signFlag[1]=1;
     memset(numB,0,sizeof(numB)) ;
}
void GetResult()							 //������
{
	Transform();
											//�ж������־λ�����м���
	if(calFlag==1)
		Result=numa/numb;
	else if (calFlag==2) 
		Result=numa*numb;
	else if (calFlag==3) 
		Result=numa-numb; 
	else if (calFlag==4) 
		Result=numa+numb; 
	
	numa=Result;							  //�޸���־λ
	if(numa<0)
	{
		signFlag[0]=-1;
		numa=-numa;
	}
	else
		signFlag[0]=1;     
	
    sprintf(numA,"%f",numa);
	char mit[101];
    strcat(mit,"-");
	
		if(signFlag[0]==1)								 //���������Ϊ��
            SetCtrlVal(panelHandle,PANEL_STRING,numA);
		else  											 //���Ϊ��
		{
		  	strcat(mit,numA); 
	        SetCtrlVal(panelHandle,PANEL_STRING,mit); 
		}
	Re();
}
	
int CVICALLBACK Reset (int panel, int control, int event,	  //����
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
		numFlag=0;
		signFlag[0]=1;
		signFlag[1]=1;
		numa=0;
		numb=0;
		Result=0;
		memset(numA,0,sizeof(numA));
		memset(numB,0,sizeof(numB));  
		break;
	} 
	Show();  
	return 0;
}

int CVICALLBACK Delet (int panel, int control, int event,	  //�˸�
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0&&numA[0]!=0)				  //��һ�����ݣ��Ҳ�Ϊ��
			{
			numA[strlen(numA)-1]='\0';
			}
			else if (numFlag==1&&numB[0]!=0)		  // �ڶ��������Ҳ�Ϊ��
			{
			numB[strlen(numB)-1]=0; 
			}	
			break;
	}
		Show();
	return 0;
}

int CVICALLBACK Divide (int panel, int control, int event,void *callbackData, int eventData1, int eventData2)	   //��
{
	
	switch (event)
	{
		case EVENT_COMMIT: 
	
	if(numB[0]!=0)						   //�ڶ������ݲ�Ϊ�գ���������
		GetResult();
	else								   //�գ��ı������־λ
		numFlag=1;
	
    calFlag=1;	  
			break;
	}
	
	return 0;
}

int CVICALLBACK input7 (int panel, int control, int event,														  //��������7
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)						  //���Ƶ�һ������ʱ
			{ 
				strcat(numA,"7");
			}
			else if(numFlag==1)					 //���Ƶڶ�������ʱ
			{ 
				strcat(numB,"7");
			}
		Show(); 
		break;
	}	 	  
	return 0;
}

int CVICALLBACK input8 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)							//���Ƶ�һ������ʱ 
			{
				strcat(numA,"8");
			}
			else if(numFlag==1)						  //���Ƶ�2������ʱ 
			{
		      	strcat(numB,"8");
			}
	    	Show();
		break;
	} 	 
	return 0;
}

int CVICALLBACK Multiply (int panel, int control, int event,												   //��
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			
		case EVENT_COMMIT:
	        if(numB[0]!=0)						//�ڶ������ݲ�Ϊ�գ���������  
	    	   GetResult();
		    else
		       numFlag=1;						 //�գ��ı������־λ
		
	      	calFlag=2;
		break;
	}

	return 0;
}

int CVICALLBACK input4 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"4");
			}
			else if(numFlag==1)
			{
				strcat(numB,"4");
			}
	     	Show(); 
		break;
	}	  
	return 0;
}

int CVICALLBACK input5 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"5");
			}
			else if(numFlag==1)
			{
				strcat(numB,"5");
			}
			Show();
			break;
	}   	   
	return 0;
}

int CVICALLBACK input6 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"6");
			}
			else if(numFlag==1)
			{
				strcat(numB,"6");
			}
		    Show();
		break;
	}  	   
	return 0;
}
																											  //��
int CVICALLBACK Minus (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			case EVENT_COMMIT: 
		  		
            	if(numB[0]!=0)
		           GetResult();
		        else
		           numFlag=1;
		
		        calFlag=3;
			break;
	}
	
	return 0;
}

int CVICALLBACK input1 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"1");
			}
			else if(numFlag==1)
			{
			strcat(numB,"1");
			}
			Show();
			break;
	}     
	return 0;
}

int CVICALLBACK input2 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			case EVENT_COMMIT: 
		         if(numFlag==0)
		    	{
				strcat(numA,"2");
		    	}
				else if(numFlag==1)
				{
				strcat(numB,"2");
				}
			    Show();
			break;
	} 	   
	return 0;
}

int CVICALLBACK input3 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
		    {
				strcat(numA,"3");
			}
			else if(numFlag==1)
			{
				strcat(numB,"3");
			}
		    Show();
		break;
	} 	  
	return 0;
}

int CVICALLBACK Plus (int panel, int control, int event,													 //��
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
        	if(numB[0]!=0)
		      GetResult();
		    else
		      numFlag=1;
			
		    calFlag=4;
		break;
	}
	return 0;
}
   
int CVICALLBACK input9 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)
			{
				strcat(numA,"9");
			}
			else if(numFlag==1)
			{
				strcat(numB,"9");
			}
			Show();
			break;
	}    
	return 0;
}
int CVICALLBACK Sign (int panel, int control, int event,												//�����ŷ�ת	
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			if(numFlag==0)						   //�Ƿ������һ������
			{
			 	signFlag[0]=-signFlag[0];
			}
				else if(numFlag==1&&numB[0]!='\0')	  //�����ڶ������ݣ��Ҳ�Ϊ��
			{
	        	signFlag[1]=-signFlag[1];  
			}
		    Show();
		break;
	}
	
	return 0;
}

int CVICALLBACK input0 (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			case EVENT_COMMIT: 
			    if(numFlag==0)
			    {
			       strcat(numA,"0");
		     	}
	        	else if(numFlag==1)
			    {
			        strcat(numB,"0");
			    }
		        Show();
		break;
	} 	   
	return 0;
}

int CVICALLBACK Point1 (int panel, int control, int event,												    //С��������  
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			case EVENT_COMMIT: 
			    if(numFlag==0)					   //�Ƿ������һ������
			    {
				    int pointFlag=0;			   //����Ƿ�����С�������
				    for(int i=0;i<100;i++)		  //ɨ��ȫ���ַ���С����
				   {
					if(numA[i]==".")
						pointFlag=1;
					
				    }
				    if(pointFlag==0)			 //��С����������С���㣬�����޲���
				    {
					strcat(numA,".");
				    }
		         }
				else if(numFlag==1)				 //�Ƿ�����ڶ������ݣ�ͬ��
				{
				    int pointFlag=0;
			     	for(int i=0;i<100;i++)
				    {
					    if(numB[i]==".")
						   pointFlag=1;
				    }
			    	if(pointFlag==0)
				    {
					   strcat(numB,".");
				    }
				}
		       Show();
		break;
	}
	
	return 0;
}

int CVICALLBACK Equal (int panel, int control, int event,												   //������
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT: 
			 		
        	if(numB[0]!=0)						//����ڶ������ݲ�Ϊ�գ�ִ������
		      GetResult();
		break;
	}
	return 0;
}

int CVICALLBACK Close (int panel, int event, void *callbackData,	 //�˳�
					   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);						   //����˳�
			break;
	}
	return 0;
}
