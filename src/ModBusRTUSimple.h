#pragma once
#include "ModbusRTU.h"
unsigned long waktuSekarang=millis(), interval=0;
String protokol;
extern ModbusRTU mb;

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) {
  if (event != Modbus::EX_SUCCESS) {
    // Serial.print("Request result: 0x");
    switch (event)
    {
    case 225:
      protokol = "Master bermasalah / error";
      break;
    
    case 226:
      protokol = "Input data tidak sesuai";
      break;
    
    case 227:
      protokol = "Tidak sesuai pembacaan antara Slave dan Master";
      break;
    
    case 228:
      protokol = "Waktu Habis / Timeout, Cek Koneksi!";
      break;
    
    case 229:
      protokol = "Sinyal Hilang, Cek Koneksi!";
      break;
    
    case 230:
      protokol = "Pertukaran data gagal / dibatalkan";
      break;
    
    default:
      break;
      
    }
    Serial.println(protokol);
  }
  return true;
}


void kirimCoil(uint16_t SLAVE_ID, uint16_t alamat, bool isi){
  if (!mb.slave()) {
    if(millis()-waktuSekarang>interval){
      mb.writeCoil(SLAVE_ID,alamat,isi,cb);
      while(mb.slave()) { 
        mb.task();
      }
      waktuSekarang = millis();
    }
    
  }
}

int bacaCoil(uint16_t SLAVE_ID,uint16_t alamat){
  bool isi;
  if (!mb.slave()) {
    if(millis()-waktuSekarang>interval){
      mb.readCoil(SLAVE_ID,alamat,&isi,1,cb);
      while(mb.slave()) { 
        mb.task();
      }
      waktuSekarang = millis();
    }
    
  }
  return isi;
}

int bacaHreg(uint16_t SLAVE_ID,uint16_t REG_COUNT){
  int arr[REG_COUNT];
  int dataBaca = REG_COUNT-1,dataSementara;
  uint16_t res[REG_COUNT];
  for(int i=0; i<REG_COUNT; i++){
    res[i]=0;
  }
  if (!mb.slave()) {
    if(millis()-waktuSekarang>interval){
      mb.readHreg(SLAVE_ID, 0, res, REG_COUNT, cb);
      while(mb.slave()) { 
        mb.task();
      }
      for(int i = 0; i<REG_COUNT; i++){
        arr[i]=res[i];
        dataSementara=arr[dataBaca];
      }
      waktuSekarang = millis();
    }
  }
  return dataSementara;
}
void tulisHreg(uint16_t SLAVE_ID, uint16_t alamat, uint16_t isi){
  if(!mb.slave()){
    if(millis()-waktuSekarang>interval){
      mb.writeHreg(SLAVE_ID,alamat,&isi,1,cb);
      while (mb.slave()){
        mb.task();
      }
      waktuSekarang = millis();
    }
  }
}