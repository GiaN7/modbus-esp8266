## API Standard

# Untuk Membaca COIL dari ModBus Slave

```c
int bacaCoil(uint16_t SLAVE_ID,uint16_t alamat);
```

# Untuk Menulis COIL ke Modbus Slave

```c
void kirimCoil(uint16_t SLAVE_ID, uint16_t alamat, bool isi);
```

# Untuk Membaca Nilai Holding Register dari Modbus Slave

```c
int bacaHreg(uint16_t SLAVE_ID,uint16_t REG_COUNT);
```

# Untuk Menulis Nilai Holding Register dari Modbus Slave

```c
void tulisHreg(uint16_t SLAVE_ID, uint16_t alamat, uint16_t isi);
```


# Keterangan
SLAVE_ID adalah Alamat Modbus Slave
alamat adalah alamat dari masing masing Register Modbus Slave
isi adalah nilai yang akan dikirimkan ke Modbus Slave
REG_COUNT adalah alamat yang akan dibaca oleh Holding Register Modbus Slave