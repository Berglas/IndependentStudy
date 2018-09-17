#include <SoftwareSerial.h> //使用藍芽模組時需引用。
#include <Servo.h> //使用伺服馬達時需引用。

// 初始化伺服馬達&設定腳位。
Servo servoClaw,servoLeft,servoRight,servoBottom;
int RM_F=8; 
int RM_B=6;
int LM_F=5;
int LM_B=7;
int Claw=20,Left=100,Right=110,Bottom=90;

//初始化藍芽版對應腳位&設定連接鮑率。
SoftwareSerial I2CBT(0,1);
I2CBT.begin(9600); 

void setup()
{  
  pinMode(RM_F,OUTPUT);
  pinMode(RM_B,OUTPUT);
  pinMode(LM_F,OUTPUT);
  pinMode(LM_B,OUTPUT);
  servoBottom.attach(3);
  servoBottom.write(90);
  servoLeft.attach(11);
  servoLeft.write(100);
  servoRight.attach(10);
  servoRight.write(110);
  servoClaw.attach(9);
  servoClaw.write(20);

}

void loop() 
{
  char cmd;
  if (I2CBT.available()>0)
  {  
       cmd=I2CBT.read();
  }
    switch (cmd) 
    {
      case 'F': //車往前
        /*
        digitalWrite(RM_F,HIGH);
        digitalWrite(RM_B,LOW);
        digitalWrite(LM_F,HIGH);
        digitalWrite(LM_B,LOW);
        */
        digitalWrite(RM_F,LOW);
        digitalWrite(RM_B,HIGH);
        digitalWrite(LM_F,LOW);
        digitalWrite(LM_B,HIGH);
        
        break;      
      case 'B':  //車往後
        /*
        digitalWrite(RM_F,LOW);
        digitalWrite(RM_B,HIGH);
        digitalWrite(LM_F,LOW);
        digitalWrite(LM_B,HIGH);
        */
        digitalWrite(RM_F,HIGH);
        digitalWrite(RM_B,LOW);
        digitalWrite(LM_F,HIGH);
        digitalWrite(LM_B,LOW);
        
        break;      
      case 'L': //車左轉
        digitalWrite(RM_F,HIGH);
        digitalWrite(RM_B,LOW);
        digitalWrite(LM_F,LOW);
        digitalWrite(LM_B,HIGH);
        
        break;      
      case 'R': //車右轉

        digitalWrite(RM_F,LOW);
        digitalWrite(RM_B,HIGH);
        digitalWrite(LM_F,HIGH);
        digitalWrite(LM_B,LOW);
        
        break;  
      case 'X': //停止動作(各按鍵放開發送)
        digitalWrite(RM_F,LOW);
        digitalWrite(RM_B,LOW);
        digitalWrite(LM_F,LOW);
        digitalWrite(LM_B,LOW);
        servoClaw.detach();
        servoLeft.detach();
        servoRight.detach();
        servoBottom.detach();               
        break;  
      case 'W':  //臂往前
        while(1)
        {
          if (I2CBT.available()>0)
          {  
               cmd=I2CBT.read();  //讀取藍芽訊息
          }
          if(cmd!='W')
          {
            break;  //如果接受到訊息不為'W'則離開此While()迴圈
          }
          servoRight.attach(10);      
          if(Right<=220)  //設定安全轉動範圍，即轉動最大值不得超過220
          {
            Right=Right+2;  //轉動伺服馬達兩個單位
            servoRight.write(Right);
            delay(50);
          }
          else
          {
            break;
          } 
        }
        break; 
      case 'S':  //臂往後
        while(1)
        {
          if (I2CBT.available()>0)
          {  
             cmd=I2CBT.read();  //讀取藍芽訊息
          }
          if(cmd!='S')
          {
            break;  //如果接受到訊息不為'S'則離開此While()迴圈
          }
          servoRight.attach(10);
          if(Right>=50)  //設定安全轉動範圍，即轉動最小值不得小於50
          {
            Right=Right-2;  //轉動伺服馬達兩個單位
            servoRight.write(Right);
            delay(50);
          }
          else
          {
            break;
          } 
        }
        break; 
      case'A': //底左轉
        while(1)
        {
          if (I2CBT.available()>0)
          {  
               cmd=I2CBT.read();  //讀取藍芽訊息
          }
          if(cmd!='A')
          {
            break;  //如果接受到訊息不為'A'則離開此While()迴圈
          }
          servoBottom.attach(3);  
          if(Bottom<=150)  //設定安全轉動範圍，即轉動最大值不得超過150
          {          
            Bottom=Bottom+4;  //轉動伺服馬達四個單位
            servoBottom.write(Bottom);
            delay(50);            
          }
          else
          {
            break;
          } 
        }
        break;
      case'D': //底右轉
        while(1)
        {
          if (I2CBT.available()>0)
          {  
             cmd=I2CBT.read();   //讀取藍芽訊息
          }
          if(cmd!='D')
          {
            break;  //如果接受到訊息不為'D'則離開此While()迴圈
          }
          servoBottom.attach(3);  
          if(Bottom>=30)  //設定安全轉動範圍，即轉動最小值不得小於30
          {          
            Bottom=Bottom-4;
            servoBottom.write(Bottom);   //轉動伺服馬達四個單位
            delay(50);
          }
          else
          {
            break;
          } 
        }  
        break; 
      case'O': //開夾
        while(1)
        {
          if (I2CBT.available()>0)
          {  
             cmd=I2CBT.read();  //讀取藍芽訊息
          }
          if(cmd!='O')
          {
            break;  //如果接受到訊息不為'O'則離開此While()迴圈
          }
          servoClaw.attach(9);  
          if(Claw<=60)  //設定安全轉動範圍，即轉動最大值不得超過60
          {
            Claw=Claw+2;  //轉動伺服馬達二個單位
            servoClaw.write(Claw);
            delay(50);
          }
        }
        break; 
      case'C': //關夾
        while(1)
        {
          if (I2CBT.available()>0)
          {  
               cmd=I2CBT.read();  //讀取藍芽訊息
          }
          if(cmd!='C')
          {
            break;  //如果接受到訊息不為'C'則離開此While()迴圈
          }
          servoClaw.attach(9);  
          if(Claw>=5)  //設定安全轉動範圍，即轉動最小值不得小於5
          {
            Claw=Claw-2;   //轉動伺服馬達二個單位
            servoClaw.write(Claw);
            delay(50);
          }
          else
          {
            break;
          } 
        }
        break;   
      case'U': //臂往上
        while(1)
        {
          if (I2CBT.available()>0)
          {  
             cmd=I2CBT.read();  //讀取藍芽訊息
          }
          if(cmd!='U')
          {
            break;  //如果接受到訊息不為'U'則離開此While()迴圈
          }
          servoLeft.attach(11);  
          if(Left<=150)  //設定安全轉動範圍，即轉動最大值不得超過150
          {
            Left=Left+3;   //轉動伺服馬達三個單位
            servoLeft.write(Left);
            delay(50);
          }
          else
          {
            break;
          }
        } 
        break;
      case'N': //臂往下
        while(1)
        {
          if (I2CBT.available()>0)
          {  
             cmd=I2CBT.read();   //讀取藍芽訊息
          }
          if(cmd!='N')
          {
            break;  //如果接受到訊息不為'N'則離開此While()迴圈
          }
          servoLeft.attach(11);
          if(Left>=85)   //設定安全轉動範圍，即轉動最小值不得小於85
          {  
              Left=Left-3;   //轉動伺服馬達三個單位
            servoLeft.write(Left);
            delay(50);
          }
          else
          {
            break;
          } 
        }
        break;     
      default:
        break;
     } //Switch
}//loop


