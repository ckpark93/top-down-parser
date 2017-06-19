
/* T1-style calculator: Parse integer arithmetic expressions into executable form. */

/*
	github.com/park3745
*/
#include <stdio.h>
#include <stdlib.h>
#define endOfFile  0
#define endOfLine  13
#define EOLN       '\n'

enum nodetype { binop, unop, number };

struct node {
	enum nodetype tag;//노드의 타입을 나타내는 변수
	char bOperator, uOperator;//연산자 변수
	int num;//피연산자 변수
	struct node *operand, *leftOperand, *rightOperand;//왼쪽,오른쪽,또는(단항연산일경우)하나의 피연산자를 가리키는 포인터
};

char savedChar = ' '; //임시로 저장하는 버퍼.
/***************************************************************************
Prototypes for functions
*****************************************************************************/
struct node *term();
struct node *expr();
struct node *factor();

char getChar(void) {
	char c;

	if (savedChar != ' ')
	{
		c = savedChar;
		savedChar = ' ';
	}//임시저장 버퍼에 문자열이 있으면 그것을 반환한다.
	else if (savedChar == EOF)
		c = (char)(endOfFile);
	else if (savedChar == EOLN)
	{
		c = (char)(endOfLine);
	}//파일,또는 입력받은 문장의 끝일경우
	else
	{
		c = getchar();
		printf("%c", c);
	}//그것도 아닌경우 다음 문자열을 불러온다. getchar()는 한 문자열만 읽는 함수.
	return(c);
}

void ungetChar(char c) {
	if (savedChar == ' ')
		savedChar = c;
	else
		printf("%c can't unget more than one character at a time", c);
	//ungetChar함수의 경우 savedChar로 한 문자열을 저장해주는 함수이다. 이것을 이용해
	//한번 읽은 뒤에 다시 해당문자열을 nextChar() 해야하는 경우가 있으면 불러올 수 있다.
}

char nextChar(void) {
	char c;

	c = getChar();
	return(c);
}//다음 문자열을 불러온다.

int charToInt(char c) {
	int charToINT;

	if (c <'0' && c > '9')
	{
		printf("charToint: %c is not a digit", c);
		charToINT = 0;
	}//0~9에 해당하는 문자열일 경우엔 int로 형변환이 가능.(ascii이용)
	else {
		charToINT = (int)(c - '0');//'0'의 ascii값을 뺌으로써 int형변환.
	}
	return (charToINT);
}
int getNum(char c) {
	int n;

	n = 0;
	do {
		n = 10 * n + charToInt(c);
		c = getChar();
	} while ('0' <= c && c <= '9');
	ungetChar(c);
	return (n);
}//문장의 다음 숫자를 불러오는 함수. 자리수가 1의자리보다 크더라도 불러올 수 있도록 만드는 함수.
//다 읽은뒤에 다음 문자를 saveChar에 저장해준다.


struct node *binopNode(char opor, struct node *lopand, struct node *ropand)
{
	struct node *n;
	/* do something */
	//이항 연산자의 경우 이 함수를 이용해 노드를 생성한다. 
	if(lopand==NULL||ropand==NULL)
		n = NULL;//좌항,우항이 NULL이면 NULL을 반환
	else{
		n = (struct node *) malloc(sizeof(struct node));
		n->tag = binop;
		n->uOperator = ' ';
		n->bOperator = opor;
		n->operand = NULL;
		n->leftOperand = lopand;
		n->rightOperand = ropand;
	}//아닌경우 메모리 할당후에, 태그와 각 구조체안의 변수들을 채워넣는다. 

	return(n);
}
struct node *unopNode(char opor, struct node *opand)
{
	struct node *n;
	//단항 연산, 문제에서 요구하는 부정 연산에 대해 할당해주는 함수
	if (opand == NULL)
		n = NULL;
	else {
		n = (struct node *)malloc(sizeof(struct node));
		n->tag = unop;
		n->uOperator = opor;
		n->bOperator = ' ';
		n->operand = opand;
		n->leftOperand = n->rightOperand = NULL;
	}
	return(n);
}

struct node *numberNode(int i)
{
	struct node *n;
	//그외에 숫자의 경우 이 함수를 통해 할당.
	n = (struct node *)malloc(sizeof(struct node));
	n->tag = number;
	n->num = i;
	n->leftOperand = n->rightOperand = n->operand = NULL;
	return(n);
}

void ptree(struct node *n, int depth) {
	switch (n->tag) {
	case binop:
		printf("%d, %c\n", depth, n->bOperator);
		ptree(n->leftOperand, depth + 2);
		ptree(n->rightOperand, depth + 2);
		break;
	case unop:
		printf("%d, %c\n", depth, n->uOperator);
		ptree(n->operand, depth + 2);
		break;
	case number:
		printf("%d, %d\n", depth, n->num);
		break;
	default:
		break;
	}
}//재귀를 통해 트리를 그리는 함수. 깊어질수록 2씩 증가시킨다. 

void PrintTree(struct node *n) {
	printf("Parse Tree:\n");
	ptree(n, 0);
}

struct node *factor(void) {
	char c;
	struct node *Factor;

	c = nextChar();

	/* do something */
	//factor :: = number | -factor | (expr)
	//factor는 정수, 부정, 괄호를 받는다. 
	if(c <='9'&&'0'<=c)
		Factor = numberNode(getNum(c));//숫자일경우 getNum을 이용해 현재 위치를 숫자가 끝나는 곳으로 이동시키고, 그만큼의 수를 자리수 계산하여 저장한다. 
	else if(c=='!'){
		Factor = unopNode(c,factor());
	}
	else if (c == '(') {//괄호인 경우, expr을 호출하고 다음 문자열을 검사한다. 
		Factor = expr();
		c = nextChar();
		if (c != ')') {//만약 )가 아닐 경우, NULL을 반환한다. NULL은 제대로 파싱이 되지않는 구문이라는 뜻이다.
			Factor = NULL;
			ungetChar(c);
		}
	}
	else
		Factor = NULL;

	return(Factor);
}

struct node *term(void) {
	char c;
	struct node *n, *Term;
	n = factor();
	/* do something */
	//파싱된 n이 NULL이 아니라면, 즉 제대로 파싱이 되었다면 다음 문자열을 비교한다. 
	//term ::= factor | factor * term | factor / term
	if(n!=NULL){
		c = nextChar();
		if(c == '*' || c=='/'){//좌항에 이전에 호출한 factor, 우항에 term이 재귀호출되도록 이항연산자 노드를 만들어준다. 
			Term = binopNode(c,n,term());//*,/에 더 높은 우선순위를 부여함.
		}
		else{//다음 문자열이 *,/이 아닐 경우 factor 그대로를 반환하기 위해 ungetChar()로 다음 문자열을 되돌려준다. 
			ungetChar(c);
			Term = n;
		}
	}
	else
		Term = n;//NULL그대로 반환

	return(Term);
}

struct node *expr(void) {
	char c;
	struct node *n, *Expr;

	n = term();
	
	/* do something */
	//마찬가지로, 파싱된 term이 NULL이 아니라면 다음 문자열을 비교.
	//expr ::= term | term + expr | term - expr
	if(n != NULL){
		c = nextChar();
		if(c=='+'||c=='-'){//이번엔 우항에 expr을 호출.
			Expr = binopNode(c,n,expr());
		}
		else{
			ungetChar(c);
			Expr = n;
		}
	}
	else
		Expr = n;

	return(Expr);
}
int eval(struct node *n) {//계산하는 함수. 노드의 오른쪽,왼쪽을 따라서 계산해나간다. 
	int op1, op2, EVAL;
	//tag를 이용해 효율적으로 계산
	switch (n->tag) {
	case binop:
		op1 = eval(n->leftOperand);
		op2 = eval(n->rightOperand);
		switch (n->bOperator) {
		case '+': EVAL = op1 + op2; break;
		case '-': EVAL = op1 - op2; break;
		case '*': EVAL = op1 * op2; break;
		case '/': EVAL = op1 / op2; break;
		}
		break;
	case unop: EVAL = -eval(n->operand);
		break;
	case number: EVAL = n->num;
		break;
	}
	return(EVAL);
}

int run(void) {
	struct node *n;

	n = NULL;
	printf("> ");
	n = expr();
	if (n != NULL) {
		printf("\n");
		PrintTree(n);
		printf("\n");
		printf("Result = %d\n", eval(n));
	}
	
	return 0;
}

void main(void) {
	printf("\n\tMy calculator: \n");
	printf("\tEnter an arithmetic expression and hit <RETURN>.\n");
	printf("\tI will print a parse tree and evaluate the expression.\n");

	run();
}
