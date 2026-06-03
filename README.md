# 🧠 Smart Lock IoT System  
**Arduino + RFID + Cloud 기반 스마트 도어락 시스템**

RFID 인증을 통해 문을 제어하고,  
Arduino IoT Cloud를 통해 원격 모니터링 및 제어가 가능한 IoT 프로젝트입니다.

---

## 📌 Overview

이 프로젝트는 **IoT Edge Device의 기본 구조를 직접 구현**하는 것을 목표로 합니다.

- RFID 기반 출입 제어  
- 서보모터 도어락 제어  
- 온도 센서 데이터 수집  
- Arduino IoT Cloud 연동  
- Dashboard 및 모바일 앱 제어  

---

## 👨‍🎓 Target

- 전자공학 / 컴퓨터공학 3~4학년  
- IoT / 임베디드 입문자  
- Arduino DIY 프로젝트 제작자  
- 캡스톤 디자인 수행자  

---

## ⚙️ Features

- 🔐 RFID 인증 기반 도어 제어  
- ⚙️ Servo Motor 잠금/해제  
- 🌡️ DHT11 온도 측정  
- ☁️ Arduino IoT Cloud 연동  
- 📱 Remote App 제어  
- 📊 Cloud Dashboard 상태 확인  

---

## 🧩 System Architecture

```
RFID Card
   ↓
RC522 Reader
   ↓
Arduino (UNO R4)
   ↓
Servo Motor (Lock)
   ↓
Arduino IoT Cloud
   ↓
Dashboard / Mobile App
```

---

## 🔄 Flow

```
1. RFID 카드 입력
2. UID 읽기
3. UUID 비교
   ├─ 일치 → 문 열림 (5초 유지)
   └─ 불일치 → 무시
4. 자동 잠금
5. Cloud 상태 업데이트
```

---

## 🧪 Hardware (BOM)

| Component | Description |
|---|---|
| Arduino UNO R4 WiFi | Main MCU |
| RC522 RFID Module | Card Reader |
| SG90 Servo Motor | Lock Control |
| DHT11 Sensor | Temperature |
| 1602 LCD (I2C) | Display |
| RFID Card/Tag | Authentication |
| Jumper Wires | Wiring |

---

## 🔌 Pin Mapping

| Function | Pin |
|---|---|
| DHT11 | D2 |
| Servo | D6 |
| RC522 SS | D10 |
| RC522 RST | D9 |
| SPI | D11, D12, D13 |
| LCD (I2C) | SDA(A4), SCL(A5) |

---

## 📱 Cloud Features

- Door 상태 실시간 확인  
- Remote App 제어  
- RFID UUID 원격 변경  
- 온도 기반 Trigger 알림  

---

## ⚠️ Limitations

- Super Loop 기반 구조  
- RFID 5초 주기 처리  
- 실시간 응답성 제한  

---

## 🔧 Improvements

- State Machine / RTOS 적용  
- Interrupt 기반 RFID 처리  
- 저전력 설계 (Sleep Mode)  
- Watchdog 적용  
- 다중 카드 등록  
- 보안 강화  

---

## 🤖 Future Work

- AI 기반 침입 감지 (IMU / 진동)  
- 배터리 수명 예측  
- 스마트홈 연동  
- 음성 제어  
- 모바일 UX 개선  

---

## 🧠 Lesson Learned

- IoT는 HW + FW + Cloud 통합 설계가 핵심  
- 구조 설계가 기능보다 중요  
- delay 기반 구조는 확장성 제한  
- Cloud 기반 설계는 유지보수에 유리  

---

## 🧱 Mechanical Design

- 3D 프린팅 케이스 적용  
- 배선 정리 및 내부 구조 개선  
- 실제 제품 형태 구현  
- 사용자 인터페이스 고려  

---

## 📸 Media (To Do)

- 회로도
  <img width="1374" height="1074" alt="image" src="https://github.com/user-attachments/assets/fa8bcecf-e399-4771-b75c-3739557d90aa" />
<br>
- Dashboard 캡처  
<img width="2692" height="834" alt="image" src="https://github.com/user-attachments/assets/9d7ce9a5-3220-4573-9dd3-84f0be89f6f0" />

---

## 📄 License

Apache 2.0

---

## ⭐ Summary

**RFID + Servo + Cloud를 결합한 IoT Smart Lock 시스템으로,  
임베디드와 클라우드 통합 구조를 학습할 수 있는 프로젝트입니다.**
