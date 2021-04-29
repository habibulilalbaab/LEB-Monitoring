# LEB-Monitoring
 Monitor your External Laptop Battery using this Program, no need to buy a new battery, create your own 3S battery, and connect it to a laptop for a long run time.


<p align="center">
  <img src="Image-Ilustration.png" />
</p>

## Setup
```
pip install -r requirements.txt
```
Edit ESP Wifi Client
```
#define STASSID "LEB-Monitoring"
#define STAPSK  "12345678"
```
Edit ESP Static IP
```
IPAddress ip(192,168,5,5);   
IPAddress gateway(192,168,5,1);   
IPAddress subnet(255,255,255,0);  
```