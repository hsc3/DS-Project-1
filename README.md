## DS_project1_2021_2
### 2021-2 Data Structure Project #1

### Due date: 2021/10/11 23h 59m 59s.

### Notice !! 윈도우에서 리눅스로 단순 파일 복사 및 드래그는 파일 인코딩 변환 문제가 발생 할 수 있으니 
### 반드시 리눅스 환경에서 파일을 재생성 후 테스트 바랍니다!!

### Notice !! 설계와 실습을 모두 수강하시는 분은 실습 과제제출란에만 제출 해주시면 됩니다 !!
### Notice !! STL은 BST의 level order 구현에서 stack STL과 heap 구현에서 vector STL만 사용가능합니다!!

#### 본 프로젝트는 계정 관리 프로그램을 구현하는 것으로 상세한 설명은 프로젝트 문서와 다음 설명을 참고한다.
##### 본 프로젝트에서는 이진 탐색 트리(Binary Search Tree, BST)와 연결 리스트(Linked List), 큐(Queue), 힙(Heap)을 이용하여 계정 관리 프로그램을 구현한다. 이 프로그램은 파일로부터 사용자 이름과 나이, 계정 ID를 읽어 Queue를 구축하며, 해당 Queue를 Account_Queue라 부른다. pop 명령을 실행하면 Queue에서 데이터를 방출하여 Account_BST와 User_List에 저장한다. Account_BST는 계정 ID와 사용자 이름으로 노드를 구성하며, 계정 ID를 기준으로 BST를 연결한다. User_List는 사용자 이름과 나이, 사용자가 보유한 계정 수로 노드를 구성하며, 노드가 입력된 순서대로 List를 연결한다. User_List에 존재하지 않는 사용자의 계정 정보가 입력될 경우 List에 노드를 추가하고, 이미 존재하는 사용자의 계정 정보가 입력될 경우 해당 노드를 수정한다. User_List의 노드는 Account_BST 노드를 가리키는 포인터를 추가로 가지며, 해당 User_List 노드의 사용자가 보유한 계정들을 Linked List로 연결한다. HeapLoad 명령을 실행하면 User_List의 정보들을 순서대로 읽어 연령대별 노드를 생성하고 User_Heap에 저장한다. User_Heap은 연령대와 연령대별 사용자 수로 노드를 구성하며, 연령대별 사용자 수를 기준으로 정렬된다. User_Heap에 존재하지 않는 연령대의 사용자 정보가 입력될 경우 Heap에 노드를 추가하고, 이미 존재하는 연령대의 사용자 정보가 입력될 경우 해당 노드의 사용자 수를 증가시킨다. 자료구조의 구축 방법과 조건에 대한 자세한 설명은 program implementation에서 설명한다.

![전체구조](https://user-images.githubusercontent.com/50433145/133085427-0165d359-205b-48b2-bf82-ead72b1d909f.png)



## <u>**Notice**</u>
--------------------------


### 1. 프로젝트 문서 및 소스코드 수정사항

#### [2021_DS_Project1_ver1.pdf](https://github.com/DSLDataStorage/DS_Project_1_2021_2/files/7174906/2021_DS_Project1_ver1.pdf)
#### UserListNode.h 수정 - int AccNum(계정 수) 변수 추가, int GetAccNum 함수 추가
```
9/13 - ver1 업로드
9/14 - ver1 밑줄 표시
9/16 - ver1 그림 수정
```


### 2. 자주들어오는 질문 

**Q. command.txt와 data.txt는 제공하지 않나요?**  
A. 네, 윈도우와 리눅스 인코딩 호환 문제로 따로 제공하지 않습니다.  

--------------------------
### Knowledge 
##### 아래 명령어 예시에서 앞의 $ 로 시작되는 부분은 명령어 입력 부분이고, 그 외 는 출력 부분임
##### 리눅스 명령어 요약
1. ls  :  list로 현재 작업중인 디렉토리의 파일 및 포함된 디렉토리 목록들을 표시 ( -a, -l 속성으로 자세한 출력 가능)
2. pwd  :  print working directory로 현재 작업중인 디렉토리의 절대경로 위치 출력
3. cd  : change directory로 디렉토리 를 변경( . : 현재 디렉토리, .. : 상위 디렉토리 ) 
```
$ ls
Documents Download
$ ls -l
drwxr-xr-x 2 user user     4096 Sep 13  2020 Documents
drwxr-xr-x 2 user user     4096 Sep 26  2020 Downloads
$ pwd
/home/user
$ cd Download
$ pwd
/home/user/Downloads
```

### requirement
##### 먼저 해당 github에 저장되어 있는 base 코드를 다운받는다.
```
$ sudo apt-get install git
$ git clone https://github.com/DSLDataStorage/DS_Project_1_2021_2.git
```

### how to compile this project
##### make명령어 실행 후 ls명령어를 통해 해당 디렉토리를 확인해 보면 run 이라는 파일이 생긴것을 확인 할 수 있다. 
```
$ make
g++ -std=c++11 -g -o run AccountBST.cpp AccountBST.h AccountBSTNode.cpp AccountBSTNode.h AccountQueue.cpp AccountQueue.h AccountQueueNode.cpp AccountQueueNode.h main.cpp Manager.cpp Manager.h UserHeap.cpp UserHeap.h UserHeapNode.cpp UserHeapNode.h UserList.cpp UserList.h UserListNode.cpp UserListNode.h

$ ls
AccountBST.cpp AccountBST.h AccountBSTNode.cpp AccountBSTNode.h AccountQueue.cpp AccountQueue.h AccountQueueNode.cpp AccountQueueNode.h main.cpp Manager.cpp Manager.h UserHeap.cpp UserHeap.h UserHeapNode.cpp UserHeapNode.h UserList.cpp UserList.h UserListNode.cpp UserListNode.h **run**
```
### how to run code
##### ./(생성된 실행파일) 의 형식으로 생성된 run 실행파일을 실행한다.
##### 실행하면 결과로 log.txt파일이 생성되면서 결과가 log.txt 에 저장된다. 
```
$ ./run
$ cat log.txt
==> command 1) QLOAD
Success
```

### how to make tar.gz
##### 압축할 파일들은 하나의 디렉토리에 모아두고 tar 명령어를 실행한다.
```
$ ls
AccountBST.cpp AccountBST.h AccountBSTNode.cpp AccountBSTNode.h AccountQueue.cpp AccountQueue.h AccountQueueNode.cpp AccountQueueNode.h main.cpp Manager.cpp Manager.h UserHeap.cpp UserHeap.h UserHeapNode.cpp UserHeapNode.h UserList.cpp UserList.h UserListNode.cpp UserListNode.h

$ tar -czvf 2020202001_DS_project1.tar.gz *
AccountBST.cpp
AccountBST.h
AccountBSTNode.cpp
...
UserListNode.h

$ ls
**2020202001_DS_project1.tar.gz** AccountBST.cpp AccountBST.h AccountBSTNode.cpp AccountBSTNode.h AccountQueue.cpp AccountQueue.h AccountQueueNode.cpp AccountQueueNode.h main.cpp Manager.cpp Manager.h UserHeap.cpp UserHeap.h UserHeapNode.cpp UserHeapNode.h UserList.cpp UserList.h UserListNode.cpp UserListNode.h
```

### how to decompress tar.gz
##### tar.gz 파일이 잘 압축되었는지 확인하기 위해 실행한다.
```
$ ls
2020202001_DS_project1.tar.gz

$ tar -xzvf 2020202001_DS_project1.tar.gz
AccountBST.cpp
AccountBST.h
AccountBSTNode.cpp
...
UserListNode.h

$ ls
2020202001_DS_project1.tar.gz AccountBST.cpp AccountBST.h AccountBSTNode.cpp AccountBSTNode.h AccountQueue.cpp AccountQueue.h AccountQueueNode.cpp AccountQueueNode.h main.cpp Manager.cpp Manager.h UserHeap.cpp UserHeap.h UserHeapNode.cpp UserHeapNode.h UserList.cpp UserList.h UserListNode.cpp UserListNode.h
```
