
/* T1-style calculator: Parse integer arithmetic expressions into executable form. */

/*
	�й� : 12121487
	�̸� : ��ġ��
*/
#include <stdio.h>
#include <stdlib.h>
#define endOfFile  0
#define endOfLine  13
#define EOLN       '\n'

enum nodetype { binop, unop, number };

struct node {
	enum nodetype tag;//����� Ÿ���� ��Ÿ���� ����
	char bOperator, uOperator;//������ ����
	int num;//�ǿ����� ����
	struct node *operand, *leftOperand, *rightOperand;//����,������,�Ǵ�(���׿����ϰ��)�ϳ��� �ǿ����ڸ� ����Ű�� ������
};

char savedChar = ' '; //�ӽ÷� �����ϴ� ����.
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
	}//�ӽ����� ���ۿ� ���ڿ��� ������ �װ��� ��ȯ�Ѵ�.
	else if (savedChar == EOF)
		c = (char)(endOfFile);
	else if (savedChar == EOLN)
	{
		c = (char)(endOfLine);
	}//����,�Ǵ� �Է¹��� ������ ���ϰ��
	else
	{
		c = getchar();
		printf("%c", c);
	}//�װ͵� �ƴѰ�� ���� ���ڿ��� �ҷ��´�. getchar()�� �� ���ڿ��� �д� �Լ�.
	return(c);
}

void ungetChar(char c) {
	if (savedChar == ' ')
		savedChar = c;
	else
		printf("%c can't unget more than one character at a time", c);
	//ungetChar�Լ��� ��� savedChar�� �� ���ڿ��� �������ִ� �Լ��̴�. �̰��� �̿���
	//�ѹ� ���� �ڿ� �ٽ� �ش繮�ڿ��� nextChar() �ؾ��ϴ� ��찡 ������ �ҷ��� �� �ִ�.
}

char nextChar(void) {
	char c;

	c = getChar();
	return(c);
}//���� ���ڿ��� �ҷ��´�.

int charToInt(char c) {
	int charToINT;

	if (c <'0' && c > '9')
	{
		printf("charToint: %c is not a digit", c);
		charToINT = 0;
	}//0~9�� �ش��ϴ� ���ڿ��� ��쿣 int�� ����ȯ�� ����.(ascii�̿�)
	else {
		charToINT = (int)(c - '0');//'0'�� ascii���� �����ν� int����ȯ.
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
}//������ ���� ���ڸ� �ҷ����� �Լ�. �ڸ����� 1���ڸ����� ũ���� �ҷ��� �� �ֵ��� ����� �Լ�.
//�� �����ڿ� ���� ���ڸ� saveChar�� �������ش�.


struct node *binopNode(char opor, struct node *lopand, struct node *ropand)
{
	struct node *n;
	/* do something */
	//���� �������� ��� �� �Լ��� �̿��� ��带 �����Ѵ�. 
	if(lopand==NULL||ropand==NULL)
		n = NULL;//����,������ NULL�̸� NULL�� ��ȯ
	else{
		n = (struct node *) malloc(sizeof(struct node));
		n->tag = binop;
		n->uOperator = ' ';
		n->bOperator = opor;
		n->operand = NULL;
		n->leftOperand = lopand;
		n->rightOperand = ropand;
	}//�ƴѰ�� �޸� �Ҵ��Ŀ�, �±׿� �� ����ü���� �������� ä���ִ´�. 

	return(n);
}
struct node *unopNode(char opor, struct node *opand)
{
	struct node *n;
	//���� ����, �������� �䱸�ϴ� ���� ���꿡 ���� �Ҵ����ִ� �Լ�
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
	//�׿ܿ� ������ ��� �� �Լ��� ���� �Ҵ�.
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
}//��͸� ���� Ʈ���� �׸��� �Լ�. ��������� 2�� ������Ų��. 

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
	//factor�� ����, ����, ��ȣ�� �޴´�. 
	if(c <='9'&&'0'<=c)
		Factor = numberNode(getNum(c));//�����ϰ�� getNum�� �̿��� ���� ��ġ�� ���ڰ� ������ ������ �̵���Ű��, �׸�ŭ�� ���� �ڸ��� ����Ͽ� �����Ѵ�. 
	else if(c=='!'){
		Factor = unopNode(c,factor());
	}
	else if (c == '(') {//��ȣ�� ���, expr�� ȣ���ϰ� ���� ���ڿ��� �˻��Ѵ�. 
		Factor = expr();
		c = nextChar();
		if (c != ')') {//���� )�� �ƴ� ���, NULL�� ��ȯ�Ѵ�. NULL�� ����� �Ľ��� �����ʴ� �����̶�� ���̴�.
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
	//�Ľ̵� n�� NULL�� �ƴ϶��, �� ����� �Ľ��� �Ǿ��ٸ� ���� ���ڿ��� ���Ѵ�. 
	//term ::= factor | factor * term | factor / term
	if(n!=NULL){
		c = nextChar();
		if(c == '*' || c=='/'){//���׿� ������ ȣ���� factor, ���׿� term�� ���ȣ��ǵ��� ���׿����� ��带 ������ش�. 
			Term = binopNode(c,n,term());//*,/�� �� ���� �켱������ �ο���.
		}
		else{//���� ���ڿ��� *,/�� �ƴ� ��� factor �״�θ� ��ȯ�ϱ� ���� ungetChar()�� ���� ���ڿ��� �ǵ����ش�. 
			ungetChar(c);
			Term = n;
		}
	}
	else
		Term = n;//NULL�״�� ��ȯ

	return(Term);
}

struct node *expr(void) {
	char c;
	struct node *n, *Expr;

	n = term();
	
	/* do something */
	//����������, �Ľ̵� term�� NULL�� �ƴ϶�� ���� ���ڿ��� ��.
	//expr ::= term | term + expr | term - expr
	if(n != NULL){
		c = nextChar();
		if(c=='+'||c=='-'){//�̹��� ���׿� expr�� ȣ��.
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
int eval(struct node *n) {//����ϴ� �Լ�. ����� ������,������ ���� ����س�����. 
	int op1, op2, EVAL;
	//tag�� �̿��� ȿ�������� ���
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
