# LOOT AT ME!

> **date**: 23.01.03. - <br>
> **author**: timothy-20 <br>
> **subject**: hadoop 강좌를 통해 학습한 내용에 대하여.<br>
> **project name**: TKMFCApplication221201

[0] 하둡을 왜 사용해야 하는가?
===


[1] 하둡 분산 파일 시스템(HDFS)에 대한 이해
===
분산 환경이란 여러대의 물리적인 서버가 하나의 클러스터처럼 동작하는 형태입니다. 
>클러스터(cluster): 여러 대의 컴퓨터들이 연결되어 하나의 시스템처럼 동작하는 **컴퓨터들의 집합**.

분산 플랫폼의 아키텍쳐로는 크게 **master - slave 구조**, **master가 없는 구조**가 있습니다.

전자는 하나의 master deamon과 n개의 slave deamon이 존재하는데 반해, 후자는 각 구성 slave deamon들이
master deamon이 가져야 하는 정보들을 공유하고 있는 형태입니다.

HDFS의 모티프가 되는 <b>GFS(Google File System)</b>는 master - slave 구조를 취하고 있습니다.
따라서 HDFS의 구조 또한 이와 동일합니다.

master - slave 구조의 핵심은 master deamon의 부하를 줄이는데 있습니다. 그렇기에 GFS의 client 서버(slave deamon)는
chuck server와 직접 연결을 맺고 데이터를 주고 받으나, master와는 파일의 이름이나 청크의 인덱스 등, 실제 데이터가 아닌
데이터의 식별자를 주고 받습니다.

이러한 master deamon의 부하를 줄이기 위한 노력은, 당연하지만 master deamon이 죽으면 **전체의 클러스터에 장애가 발생**하기 때문입니다.

[1.1] Google Platform의 철학
---
Google Plaform은 아래의 4가지 철학을 가지고 있는데
- 한 대의 고가 장비보다(**Scale-up**) 여러 대의 저가 장비가 낫다(**Scale-out**).
- 데이터를 **분산 저장**한다.
  - 1개 이상의 cpu, memory를 통한 다중 처리의 의미에 더 가까운 병렬(parallel)과 구분해야 하는 개념입니다. 
  - 분산(distribute)은 데이터에 더 친숙한 개념입니다.
- 시스템(H/W)는 언제나 죽을 수 있다, 따라서 더 나은 소프트웨어를 통해 보완한다.
- 시스템 확장이 쉬워야 한다.

한마디로 **분산과 자동화**라 할 수 있겠습니다. 

[1.2] 하둡의 특성
---
- 수천 대 이상의 리눅스 기반 서버들을 하나의 클러스터로 사용.
  - On-premises의 물리적인 형태로도 구현 가능하고, 클라우드의 vm 형태로도 가능합니다.
- master - slave 구조.
- 파일을 블록(block) 단위로 저장.
- 블록 데이터의 복제본 유지.
  - 예를 들어, 100mb 크기의 데이터를 저장한다고 했을 때, 300mb의 공간을 사용합니다. 이는 하둡이 기본적으로 하나의 데이터에 대해 3개의 복제본을 가지기 때문입니다.
- 높은 내고장성(Fault-Tolerance)을 가짐.
- 데이터 처리의 지역성을 보장.

[1.3] 하둡 클러스터 네트워크 및 데몬 구성
---
해당 부분 복습하고 다시 정리할 것.

[1.4] 하둡에서 블록(Block)이란?
---
하둡에서는 하나의 파일을 설정된 단위로 나눕니다. 이때 발생하는 조각을 블록이라고 하며 대개 64mb(~v1.0) 또는 128mb(최신 버전) 크기를 가집니다.
파일이 블록의 크기보다 작거나, 작아지는 시점에는 실제 파일 그대로 블록을 구성합니다.

기본적으로 블록이 큰 이유는 탐색 비용을 최소화하기 위함입니다. 이는 파일의 탐색에 사용하는 자원을 줄이고,
네트워크를 통해 데이터를 전송할 때 자원의 사용을 집중할 수 있습니다.