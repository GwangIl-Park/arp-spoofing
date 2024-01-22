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
  - 공격자 : ubuntu (192.168.56.114, 08:00:27:b5:4c:XX)
  - 공격 대상 : windows 10 (192.168.56.1, 0a:00:27:00:00:XX)
  - 공격 대상 2 IP : 192.168.56.110

1. 초기 상태 확인

- 공격자 arp 테이블
```
gipark@gipark-VirtualBox:~/arp-spoofing$ arp -a
? (10.100.#.#) at 52:54:00:12:35:XX [ether] on enp0s3
_gateway (10.100.2.1) at 52:54:00:12:35:XX [ether] on enp0s3
? (169.254.169.254) at <incomplete> on enp0s3
```

- 공격 대상의 arp 테이블
```
C:\Users\rkasu>arp -a

인터페이스: 192.168.56.1 --- 0x9
  인터넷 주소           물리적 주소           유형
  192.168.56.255        ff-ff-ff-ff-ff-ff     정적
  224.0.0.22            01-00-5e-00-00-XX     정적
  224.0.0.251           01-00-5e-00-00-XX     정적
  224.0.0.252           01-00-5e-00-00-XX     정적
  239.192.152.143       01-00-5e-40-98-XX     정적
  239.255.255.250       01-00-5e-7f-ff-XX     정적
```



2. 패킷 확인

a. 공격 과정 (1) ping

- ping을 보내면서 arp request가 함께 발생
<img width="778" alt="image" src="https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/9a905585-1de8-4a18-a7f5-377f9f652225">

- arp reply
<img width="580" alt="image" src="https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/2a1e97a3-1cf1-4961-b900-a2b4890740d6">

b. 공격 과정 (2) arp spoof

- arp spoof 패킷
<img width="630" alt="image" src="https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/9f422da3-626a-4714-be53-d69e16b830ed">

- 패킷 내용 (공격대상2 (192.168.56.110) 의 MAC 주소가 공격자의 MAC 주소 (08:00:27:b5:4c:XX)라고 알림)
<img width="363" alt="image" src="https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/e060ac84-2565-4ab4-8126-a3a429c16fec">


1. 결과

- 공격자 arp 테이블에 공격 대상 정보 추가
```
gipark@gipark-VirtualBox:~/arp-spoofing$ arp -a
? (10.100.2.2) at 52:54:00:12:35:XX [ether] on enp0s3
? (192.168.56.1) at 0a:00:27:00:00:XX [ether] on enp0s8
_gateway (10.100.2.1) at 52:54:00:12:35:XX [ether] on enp0s3
? (169.254.169.254) at <incomplete> on enp0s3
```

- 공격 대상 arp 테이블 확인
```
C:\Users\rkasu>arp -a

인터페이스: 192.168.56.1 --- 0x9
  인터넷 주소           물리적 주소           유형
  192.168.56.110        08-00-27-b5-4c-XX     동적
  192.168.56.114        08-00-27-b5-4c-XX     동적
  192.168.56.255        ff-ff-ff-ff-ff-ff     정적
  224.0.0.22            01-00-5e-00-00-XX     정적
  224.0.0.251           01-00-5e-00-00-XX     정적
  224.0.0.252           01-00-5e-00-00-XX     정적
  239.192.152.143       01-00-5e-40-98-XX     정적
  239.255.255.250       01-00-5e-7f-ff-XX     정적
```

- 공격 대상 2에 ping을 날렸으나 공격자의 mac주소로 패킷이 나가는 모습

<img width="453" alt="image" src="https://github.com/GwangIl-Park/arp-spoofing/assets/40749130/c074ce38-503e-4476-9696-9940e681832b">


# TODO

1. 설정 파일 최적화
2. target 1, 2 arp spoofing 후, 패킷 sniffing 동작 추가
3. 로그 공통화
4. 코드 리팩토링
