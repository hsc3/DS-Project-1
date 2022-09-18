### 데이터구조설계 1차 프로젝트

#### 본 프로젝트는 계정 관리 프로그램을 구현하는 것으로 상세한 설명은 프로젝트 문서를 참고한다.
##### 본 프로젝트에서는 이진 탐색 트리(Binary Search Tree, BST)와 연결 리스트(Linked List), 큐(Queue), 힙(Heap)을 이용하여 계정 관리 프로그램을 구현한다. 이 프로그램은 파일로부터 사용자 이름과 나이, 계정 ID를 읽어 Queue를 구축하며, 해당 Queue를 Account_Queue라 부른다. pop 명령을 실행하면 Queue에서 데이터를 방출하여 Account_BST와 User_List에 저장한다. Account_BST는 계정 ID와 사용자 이름으로 노드를 구성하며, 계정 ID를 기준으로 BST를 연결한다. User_List는 사용자 이름과 나이, 사용자가 보유한 계정 수로 노드를 구성하며, 노드가 입력된 순서대로 List를 연결한다. User_List에 존재하지 않는 사용자의 계정 정보가 입력될 경우 List에 노드를 추가하고, 이미 존재하는 사용자의 계정 정보가 입력될 경우 해당 노드를 수정한다. User_List의 노드는 Account_BST 노드를 가리키는 포인터를 추가로 가지며, 해당 User_List 노드의 사용자가 보유한 계정들을 Linked List로 연결한다. HeapLoad 명령을 실행하면 User_List의 정보들을 순서대로 읽어 연령대별 노드를 생성하고 User_Heap에 저장한다. User_Heap은 연령대와 연령대별 사용자 수로 노드를 구성하며, 연령대별 사용자 수를 기준으로 정렬된다. User_Heap에 존재하지 않는 연령대의 사용자 정보가 입력될 경우 Heap에 노드를 추가하고, 이미 존재하는 연령대의 사용자 정보가 입력될 경우 해당 노드의 사용자 수를 증가시킨다.

![전체구조](https://user-images.githubusercontent.com/50433145/133085427-0165d359-205b-48b2-bf82-ead72b1d909f.png)
