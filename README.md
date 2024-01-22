# arp-spoofing

해당 프로젝트는 연구 및 학습용으로만 사용합니다.

# 사용 방법

1. settings.txt.example를 settings.txt로 복사 후, 설정 입력

- example
```
target1_ip=192.168.56.1
target2_ip=192.168.56.110

interface_name=eth0
```

2. main path에서 make

```
make
```

3. 실행

```
sudo ./arp_spoof
```

# 공격 과정

1. arp 테이블에 공격 대상 정보가 없다면 공격 대상 mac 주소를 확인하기 위해, ping을 날림

2. ARP (echo request)를 통해 공격 대상 2의 ip주소를 공격자의 mac주소라고 알림

3. (TODO) 공격 대상 1, 2에 모두 arp spoof 공격을 한 후, 패킷 스니핑

# 테스트

- 환경
  - 공격자 : ubuntu (192.168.56.114, 08:00:27:b5:4c:71)
  - 공격 대상 : windows 10 (192.168.56.1, 0a:00:27:00:00:09)
  - 공격 대상 2 IP : 192.168.56.110

1. 초기 상태 확인

- 공격자 arp 테이블
```
gipark@gipark-VirtualBox:~/arp-spoofing$ arp -a
? (10.100.#.#) at 52:54:00:12:35:00 [ether] on enp0s3
_gateway (10.100.2.1) at 52:54:00:12:35:00 [ether] on enp0s3
? (169.254.169.254) at <incomplete> on enp0s3
```

- 공격 대상의 arp 테이블
```
C:\Users\rkasu>arp -a

인터페이스: 192.168.56.1 --- 0x9
  인터넷 주소           물리적 주소           유형
  192.168.56.255        ff-ff-ff-ff-ff-ff     정적
  224.0.0.22            01-00-5e-00-00-16     정적
  224.0.0.251           01-00-5e-00-00-fb     정적
  224.0.0.252           01-00-5e-00-00-fc     정적
  239.192.152.143       01-00-5e-40-98-8f     정적
  239.255.255.250       01-00-5e-7f-ff-fa     정적
```



2. 패킷 확인

a. 공격 과정 (1) ping

- ping을 보내면서 arp request가 함께 발생
![image](https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/396fa69a-3fcd-40d4-97ba-db9e922ec10c)

- arp reply
![image](https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/bd8a01e0-5540-42c1-a1a4-3e3bdd9a62e1)

b. 공격 과정 (2) arp spoof

- arp spoof 패킷
![image](https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/7c6ad62a-82f7-41fa-bfde-ef0aefb988cd)

- 패킷 내용 (공격대상2 (192.168.56.110) 의 MAC 주소가 공격자의 MAC 주소 (08:00:27:b5:4c:71)라고 알림)
![image](https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/369ea38d-dacd-4bb5-879f-d16470e4e94f)

1. 결과

- 공격자 arp 테이블에 공격 대상 정보 추가
```
gipark@gipark-VirtualBox:~/arp-spoofing$ arp -a
? (10.100.2.2) at 52:54:00:12:35:00 [ether] on enp0s3
? (192.168.56.1) at 0a:00:27:00:00:09 [ether] on enp0s8
_gateway (10.100.2.1) at 52:54:00:12:35:00 [ether] on enp0s3
? (169.254.169.254) at <incomplete> on enp0s3
```

- 공격 대상 arp 테이블 확인
```
C:\Users\rkasu>arp -a

인터페이스: 192.168.56.1 --- 0x9
  인터넷 주소           물리적 주소           유형
  192.168.56.110        08-00-27-b5-4c-71     동적
  192.168.56.114        08-00-27-b5-4c-71     동적
  192.168.56.255        ff-ff-ff-ff-ff-ff     정적
  224.0.0.22            01-00-5e-00-00-16     정적
  224.0.0.251           01-00-5e-00-00-fb     정적
  224.0.0.252           01-00-5e-00-00-fc     정적
  239.192.152.143       01-00-5e-40-98-8f     정적
  239.255.255.250       01-00-5e-7f-ff-fa     정적
```

- 공격 대상 2에 ping을 날렸으나 공격자의 mac주소로 패킷이 나가는 모습

![image](https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/836fcff7-d1b5-452c-9210-16ce48d6a0e5)

# TODO

1. 설정 파일 최적화
2. target 1, 2 arp spoofing 후, 패킷 sniffing 동작 추가
3. 로그 공통화
4. 코드 리팩토링