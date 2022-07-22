#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//The parsing table with action and state portions
string parse_table[6][13] = {
	{"id", "s5", "no", "no", "no", "s5", "no", "s5", "s5", "no", "no", "no", "no"},
	{"+", "no", "s6", "r2", "r4", "no", "r6", "no", "no", "s6", "r1", "r3", "r5"},
	{"*", "no", "no", "s7", "r4", "no", "r6", "no", "no", "no", "s7", "r3", "r5"},
	{"(", "s4", "no", "no", "no", "s4", "no", "s4", "s4", "no", "no", "no", "no"},
	{")", "no", "no", "r2", "r4", "no", "r6", "no", "no", "s11", "r1", "r3", "r5"},
	{"$", "no", "acc", "r2", "r4", "no", "r6", "no", "no", "no", "r1", "r3", "r5"}
};

//The GOTO table
int goto_table[3][13] = {
	{1,1,0,0,8,0,0,0,0,0,0,0,0},
	{2,0,0,0,2,0,9,0,0,0,0,0,0},
	{3,0,0,0,3,0,3,10,0,0,0,0,0}
};

int top = 0;
int last = 0;
int cntr = 0;
string action;

//The table to realize how many elements will be popped out of stack
int rule_table[6][2] = {{4, 6},	{4, 2},	{19, 6}, {19, 2}, {5, 6}, {5, 2}};

typedef struct LL{
	string data;
	struct LL *next;
}ll;

//The function to get the input and create the linked list for input data
void input(ll **n){
	char data;
	ll *ptr = (*n);
	while(scanf("%c", &data)!=EOF){
		if (data == ' ' || data == '\n')
			continue;
		ll *new_node = new ll;
		if (data == 'i'){
			new_node->data = "id";
			cin>>data;
			last+=2;
		}
		else{
			new_node->data = data;
			last++;
		}
		new_node->next = NULL;
		if (*n == NULL){
			*n = new_node;
		}
		else{
			ptr = (*n);
			while(ptr->next!=NULL){
				ptr = ptr->next;
			}
			ptr->next = new_node;
		}
	}
	ll *new_node = new ll;
	new_node->data = '$';
	new_node->next = NULL;
	ptr = (*n);
	while(ptr->next!=NULL){
		ptr = ptr->next;
	}
	ptr->next = new_node;
}

//The function to create stack with input values
void push_st(string stack[1000], string data){
	if (data=="id" || data == "11")
		cntr+=2;
	else
		cntr++;
	stack[++top] = data;
}

//The function to print the current stack, input list and action list
void print(string stack[1000], ll *n){
	for (int i = 0; i <= top; ++i)
	{
		cout<<stack[i];
	}
	cout<<"\t\t\t\t\t";
	while(n!=NULL){
		cout<<n->data;
		n = n->next;
	}
	cout<<"\t\t\t\t\t";
}

//The function to find the action status
void search_a(string data, int pos){
	for (int i = 0; i < 6; ++i){
		if (parse_table[i][0] == data){
			action = parse_table[i][++pos];
			break;
		}
	}
}

//The function to delete the top of linked list as it is pushed into stack
void pop_head(ll **n, string stack[1000]){
	ll *ptr = (*n);
	push_st(stack, ptr->data);
	if (action[2] == '1')
		push_st(stack, "11");
	else
		push_st(stack, to_string(action[1]-'0'));
	if (ptr->data == "id")
		last-=2;
	else
		last--;
	ptr = ptr->next;
	(*n) = ptr;
}

//The function to pop the elements with the according value of rule table from stack
void pop_st(string stack[1000], int count){
	for (int i = 0; i < count; ++i)
	{
		if (stack[top] == "id" || stack[top] == "11")
			cntr-=2;
		else
			cntr--;
		stack[top--] = "";
	}
}

//The function to implement shift-reduce algorithm
void shift_reduce(string stack[1000], ll **n){
	while (1){
		ll *ptr = *n;
		int pos = stoi(stack[top]);
		search_a(ptr->data, pos);
		print(stack, *n);
		if (action == "no")
			break;
		if (action == "acc"){
			cout<<"\n\nACCEPTED";
			return;
		}
		else if(action[0] =='s'){
			pop_head(n, stack);
			cout<<action<<endl;
		}
		else if(action[0] == 'r'){
			int rule = action[1]-'0';
			int count = rule_table[rule-1][1];
			int o = rule_table[rule-1][0];
			string c;
			c = o + 'A';
			pop_st(stack, count);
			int goto_k = stoi(stack[top]);
			cout<<action<<"\tGOTO["<<stack[top]<<","<<c<<"]"<<endl;
			push_st(stack, c);
			int goto_i;
			switch(o){
				case 4:
					goto_i = 0;
					break;
				case 19:
					goto_i = 1;
					break;
				case 5:
					goto_i = 2;
					break;
			}
			string pos = to_string(goto_table[goto_i][goto_k]);
			push_st(stack, pos);
		}
	}
	cout<<"\n\nINVALID SYNTAX";
}

//Driver function
int main(){
	ll *head = NULL;
	string stack[1000]={"0"};
	input(&head);
	// pop_head(&head);
	cout<<"STACK\t\t\t\t\t\tINPUT\t\t\t\t\t\tACTION"<<endl;
	shift_reduce(stack, &head);
}