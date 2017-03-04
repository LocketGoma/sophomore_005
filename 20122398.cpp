#include <iostream>
#include <cstdlib>
using namespace std;
// 으아아아아아아아아악
// 시그윈에서 NULL이 되던가?

//template <typename T>

class Node { // 그냥 int로 짜야징
			 //template <typename T>
			 //friend Tree; <-이게 문제
public:
	Node();
	Node(int tp, int ky);
	int get_data(); // 내용 리턴
	~Node();
	bool lhs(); // 레프트 존재여부 확인
	bool rhs(); // 라이트 존재여부 확인
	//void setter(Node *node, bool count); //넣어욧

	Node *next(bool index);



	Node *left;
	Node *right;
//private :
	int data;
	int key=1; // 혹시 모르니 키 추가
};

class Tree { // 이게 중요함
	friend Node;
public:
	Tree();
	~Tree();
	//void insert(T node, function<int(T&, T&)& comp); // 삽입
	void insert(int node, int key);
	void insert_node(Node *current, int data, int key); // 삽입 내부 함수
	//T get(int key); // 뭘 리턴하죠? Node니 Tree니 T니
	int get(int key);
	void get_all();

	void remove(int point); // 삭제
	Node*& left_most(Node*& current);
	void replacer(Node*& replaced, Node*& newone);
	void inner_remove(Node*& current,int point);

	
	//void preorder(); // 전위 함수
	//void inorder(); // 중위 함수
	int postorder(int key); // 후위 함수
	void inner_post(Node *current, int cur);

	//void replace(); // remove 종속 함수, 노드 위치 복귀
	
	bool is_empty();


private:
	Node* root=NULL;
	int level=1;
	int current_data;
};
int main() {
	Tree tr;
	tr.insert(32,3);
	tr.insert(54,5);
	tr.insert(77,7);
	tr.insert(41,4);
	tr.insert(10,1);
	tr.insert(21,2);
	tr.insert(100,10);
	tr.insert(98,9);
	tr.insert(83,8);
	tr.insert(64,6); // 일단 여기까지
	cout<<tr.get(5)<<endl;
	tr.get_all();
	tr.remove(2);
	tr.get_all();
	tr.remove(9);
	tr.get_all();
	cout << tr.get(3) << endl;

}
Node::Node() {
	left = NULL;
	right = NULL;	
}
Node::Node(int tp,int ky) {
	data = tp;
	key = ky;
	left = NULL;
	right = NULL;
}
Node::~Node() { // 추가 안함
	data = NULL;
	//free(left);
	//free(right);
}
int Node::get_data() {
	if (data == NULL) {
		return 0;
	}
	else {
		return data;
	}
}
bool Node::lhs() {
	if (left == NULL) {
		return true;
	}
	else
		return false;
}
bool Node::rhs() {
	if (right == NULL) {
		return true;
	}
	else
		return false;
}
Node * Node::next(bool index) {
	if (index) {
		return left;
	}
	else
		return right;
}

Tree::Tree() {
	;
}

Tree::~Tree() {
	;
}
void Tree::insert(int data,int key) { //삽입 구문
	if (root == NULL) {
		Node *node = new Node(data,key);
		root = node;
	}
	else {
		insert_node(root,data,key);
	}
}

void Tree::insert_node(Node *current,int data,int key) { // 비면 넣고 아님 다음으로
			//이원 탐색. 루트보다 작으면 좌, 크면 우
			//아 비교를 get으로...
	if (current->data > data) { // 노드보다 작으면
		//level++;
		if (current->left == NULL) {
			current->left = new Node(data,key);
		}
		else {
			insert_node(current->left, data,key);
			//cout << "왼쪽" << endl;
		}
	}
	else if (current->data < data){ // 노드보다 크면
		//level++;
		if (current->right == NULL) {
			current->right = new Node(data,key);
		}
		else {
			insert_node(current->right, data,key);
			//cout << "오른쪽" << endl;
		}
	}
	get_all();
}
int Tree::get(int key) { // key값 이용 데이터 출력 <- int 가 되어야 됨

	if (is_empty()) {
		return -1;
	}
	else
	return postorder(key);
	
}
void Tree::get_all() { // 전체 출력 : key 값에 -1을 받으면 실행시킬 예정
	int i = 1;
	while (i<11) {		
		cout << "출력" << get(i++) << endl;
	}
}
int Tree::postorder(int key) {
	current_data=-1;
	inner_post(root, key);
	return current_data;
}
void Tree::inner_post(Node *current, int cur) {
	if (current == NULL || current==NULL) {
		//cout << "엄는데여" << endl;
		return ;
	}

		inner_post(current->left, cur);
		inner_post(current->right, cur);
		if (cur == current->key) {
			cout << "데이터 값 :" << current->data << endl;
			cout << "cur 값 : " << current->key << endl;
			current_data = current->data;
	}

	
}
Node*& Tree::left_most(Node*& current) { // 여기가 문제
	while (current->left!=NULL) {
		current = current->left;
	}
	return current;
}
//void -> Node*
void Tree::replacer(Node*& replaced, Node*& newone) { // 여기 먹통 <- 이전 자리에 부착이 안됨
	if (replaced == NULL || newone == NULL)
		;
	if (replaced->left != NULL && replaced->right != NULL) {
		newone->left = replaced->left;
		if (replaced->right != newone) {
			newone->right = replaced->right;
		}
	}
	//get(newone->key);
	//get(replaced->key);
	Node *temp = replaced;
	replaced = newone;
	//replaced->data = newone->data;
	//replaced->key = newone->key;
	//get(replaced->key);
	//free(temp);
	//return replaced; //<- 님 지금 뭐 리턴하세요?
}
void Tree::remove(int point) { // leftmost 삭제
	inner_remove(root,point);
}
void Tree::inner_remove(Node*& current, int point) {
	if (current->key == point) {
		if (current->left == NULL && current->right == NULL) {
			delete current;
			current = NULL;
		}
		else if (current->left != NULL && current->right == NULL) { // left 있을때
			replacer(current, current->left);
		}
		else if (current->left == NULL && current->right != NULL) // right 있을때
			replacer(current, current->right);
		else if (current->left != NULL && current->right != NULL) {// 둘다 있을때
			cout << "변환 우측" << current->right->key << endl; // 5, current = 3
			Node *move = current->right;
			replacer(current, left_most(move));
		}// current에 왜 4가 들어가는지에 대해...
	}
	else if (current->key > point) // 좌측으로
		inner_remove(current->left, point);
	else {
		inner_remove(current->right, point);
	}
	

}
bool Tree::is_empty() {
	if (root == NULL) {
		return true;
	}
	return false;
}