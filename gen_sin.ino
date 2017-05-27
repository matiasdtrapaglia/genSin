int W_CLK = 2;
int FQ_UP = 3;
int RESET = 4;

int D0 = 5, D1 = 6, D2 = 7, D3 = 8, D4 = 9, D5 = 10, D6 = 11, D7 = 12;
int palabra, resto, leer, i;
long frec;
int lectura;
int POTE1 = A1, POTE2 = A2, POTE3 = A3, POTE4 = A4, POTE5 = A5, POTE6 = A6;
int retardo = 10 ;
const float resolucion = 0.0291;


void setup() {
  pinMode(W_CLK, OUTPUT);
  pinMode(FQ_UP, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(D0, OUTPUT); pinMode(D1, OUTPUT); pinMode(D2, OUTPUT); pinMode(D3, OUTPUT); pinMode(D4, OUTPUT); pinMode(D5, OUTPUT); pinMode(D6, OUTPUT); pinMode(D7, OUTPUT);
 // pinMode(POTE1, OUTPUT); pinMode(POTE2, OUTPUT); pinMode(POTE3, OUTPUT); pinMode(POTE4, OUTPUT); pinMode(POTE5, OUTPUT); 
  //      x00K                     x0K                    xK                       x00			           xx
 // pinMode(SW, INPUT);
  digitalWrite(W_CLK, LOW);
  digitalWrite(FQ_UP, LOW);
  digitalWrite(RESET, LOW);
//  digitalWrite(POTE1, LOW); digitalWrite(POTE2, LOW); digitalWrite(POTE3, LOW); digitalWrite(POTE4, LOW); digitalWrite(POTE5, LOW); 
}

void loop() {
  //1.073.883 = 1M(999.999,8496)		107388 = 100k(99.999,7056)		10739 = 10k(10.000,1568)		1074 = 1k (1.000,1088)	107 = 100 (99,6384)
//  digitalWrite(POTE1, HIGH); digitalWrite(POTE5, LOW);	//cientos
  delay(retardo);
  lectura = analogRead(POTE1);
  //lectura = constrain(lectura, 10, 1010);
  frec = ((lectura*10/1024) / 0.0291);
  
  delay(retardo);
  lectura = analogRead(POTE2);
  for (i=0;i<10;i++) 
    if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
      frec += (10L*i / 0.0291);
  
  delay(retardo);
  lectura = analogRead(POTE3);
  for (i=0;i<10;i++) 
	  if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
		  frec += (100L*i / 0.0291);
  
  /*
  delay(retardo);
  lectura = analogRead(POTE4);
  for (i=0;i<10;i++) 
    if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
		  frec += (long)(1000*i / 0.0291);
  
  delay(retardo);
  lectura = analogRead(POTE5);
  for (i=0;i<10;i++) 
    if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
		  frec += (10000L*i / 0.0291);
  
  delay(retardo);
  lectura = analogRead(POTE6);
  for (i=0;i<10;i++) 
    if((lectura>=102.4*i-51.2)&&(lectura<102.4*(i+1)-51.2))   // Se busca
		  frec += (100000L*i / 0.0291);
  */
  frecuency(frec);
  delay(100);
}

void frecuency(long freq){
  palabra = 0;
  digitalWrite(RESET, HIGH); delay(1); digitalWrite(RESET, LOW);
  cargarDatos(palabra); //word 0    =   Fase y control
  palabra = freq / pow(2,24);
  cargarDatos(palabra); //word 1	=	Frec-b31 / Frec-b24
  palabra = (freq & (long)(pow(2,24)-1) ) / pow(2,16);		  //-65535
  cargarDatos(palabra); //word 2	= 	Frec-b23 / Frec-b16
  palabra = (freq & (long)(pow(2,16)-1) ) / pow(2,8);      								
  cargarDatos(palabra); //word 3	=	Frec-b15 / Frec-b8
  palabra = (freq & (long)(pow(2,8)-1)   ) ;									// b5 = 0.9312 Hz
  cargarDatos(palabra); //word 4	=	Frec-b7  / Frec-b0      // LSB = 0.0291 Hz
  digitalWrite(FQ_UP, HIGH); digitalWrite(FQ_UP, LOW); 
}

void cargarDatos(int data){
  digitalWrite(D0, bitRead(data,0));
  digitalWrite(D1, bitRead(data,1));
  digitalWrite(D2, bitRead(data,2));
  digitalWrite(D3, bitRead(data,3));
  digitalWrite(D4, bitRead(data,4));
  digitalWrite(D5, bitRead(data,5));
  digitalWrite(D6, bitRead(data,6));
  digitalWrite(D7, bitRead(data,7));
  digitalWrite(W_CLK, HIGH);
  digitalWrite(W_CLK, LOW);
}



