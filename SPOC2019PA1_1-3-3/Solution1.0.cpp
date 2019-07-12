/*
Author: Snickeen.
Email : ff@snickeen.com
Date  : 2019.07.03 Wed.


If you find out any bugs, please tell me. Thank you.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN (4000006)

/******************************************************/


struct _NODE{
    char c;
    //int mark[2];  // 1: direction from head to tail   0: direction from tail to head
    //char leftmark, rightmark; //
    struct _NODE *neighbour[2]; // same to mark[].
};
typedef struct _NODE NODE;

struct _LIST{
    NODE head,tail;
    NODE *lcleft,*lcright, *rcleft,*rcright; //leftcursor's left and right, rightcursor's left and right
    int LC_RC; // the distance between leftcursor and rightcursor
    //int LcLeftMark,LcRightMark; // the directions of left cursor
    //int RcLeftMark,RcRightMark;
    int counter;
};
typedef struct _LIST LIST;

LIST editor;

void Print(NODE *p){
    //puts("--------");
    printf("-- %p ",p);
    //printf("%c %d %d ", p->c, p->mark[0], p->mark[1]);
    printf(" %c  ",p->c);
    printf("%p %p\n", p->neighbour[0], p->neighbour[1]);
    //puts("--------------");
}
void Printedt(){
    puts("===========================\neditor :");
    printf("%p %p\n", &(editor.head), &(editor.tail));
    //printf("%d %d %d %d\n",editor.lcleft, editor.lcright, editor.rcleft, editor.rcright);
    printf("%p %p %p %p\n",editor.lcleft, editor.lcright, editor.rcleft, editor.rcright);
    printf("%d %d    ", editor.LC_RC, editor.counter);
    //printf("%d %d %d %d\n",editor.LcLeftMark, editor.LcRightMark, editor.RcLeftMark, editor.RcRightMark);
    puts("=======================================");
}
int debug(LIST *edt){
    puts("\n\n");
    Printedt();Print(&(edt->head));
    NODE *now = edt->head.neighbour[1];
    //NODE *End = &(edt->tail);
    int dir = 1;
    int counter = edt->counter;
    while( counter-- > 0 ){
        Print(now);
        now = now->neighbour[dir];
    }
    Print(&(edt->tail));
    //printf("%d %d %d %d\n",edt->lcleft, edt->lcright, edt->rcleft, edt->rcright);
    //printf("%d %d %d %d\n",edt->LcLeftMark, edt->LcRightMark, edt->RcLeftMark, edt->RcRightMark);
    //printf("%d %d\n",edt->LC_RC, edt->counter);
    puts("\n\n");
    return 1;
}

void initnode(NODE *node){
    node->c = '-';
    //node->mark[0] = node->mark[1] = 0;
    node->neighbour[0] = node->neighbour[1] = NULL;
}

void Init(LIST *edt,char s[]){
    int i, len = strlen(s);

    initnode(&(edt->head));initnode(&(edt->tail));
    NODE *pre = &(edt->head);
    NODE *post = &(edt->tail);
    edt->head.neighbour[1] = post;
    edt->tail.neighbour[0] = pre;

    for(i=0;i<len;i++){
        NODE *now = (NODE*)malloc(sizeof(NODE));
        //initial
        initnode(now);
        now->c = s[i];

        //Link them
        pre->neighbour[1] = now;
        now->neighbour[0] = pre;
        post->neighbour[0] = now;
        now->neighbour[1] = post;

        //Print(pre);Print(now);Print(post);
        //
        pre=now;
    }

    edt->lcleft = &(edt->head);
    edt->lcright = edt->head.neighbour[1];
    edt->rcleft = edt->tail.neighbour[0];
    edt->rcright = &(edt->tail);

    edt->LC_RC = len;

    //edt->LcLeftMark = edt->RcLeftMark = 0;
    //edt->LcRightMark = edt->RcRightMark = 1;

    edt->counter = len;

    //Printedt();
}

int MoveLeft(LIST *edt, char cursor){
    if(cursor == 'L'){
        if(edt->lcleft == &(edt->head))return 0;
        edt->lcright = edt->lcleft;
        edt->lcleft = edt->lcleft->neighbour[0];
        edt->LC_RC += 1;
    }
    else {
        if(edt->rcleft == &(edt->head))return 0;
        edt->rcright = edt->rcleft;
        edt->rcleft = edt->rcleft->neighbour[0];
        edt->LC_RC -= 1;
    }
    return 1;
}

int MoveRight(LIST *edt, char cursor){
    if(cursor == 'L'){
        if(edt->lcright == &(edt->tail))return 0;
        edt->lcleft = edt->lcright;
        edt->lcright = edt->lcright->neighbour[1];
        edt->LC_RC -= 1;
    }
    else {
        if(edt->rcright == &(edt->tail))return 0;
        edt->rcleft = edt->rcright;
        edt->rcright = edt->rcright->neighbour[1];
        edt->LC_RC += 1;
    }
    return 1;
}

int Insert(LIST *edt, char cursor, char c){
    if(c<33 || c>126){
        //puts("Something is wrong.");
        return 0;
    }

    // 创建新的节点
    NODE *now = (NODE*)malloc(sizeof(NODE));
    initnode(now);
    now->c = c;
    // 左光标
    if(cursor == 'L'){
        // 连接新节点
        edt->lcleft->neighbour[1] = now;
        edt->lcright->neighbour[0] = now;
        now->neighbour[0] = edt->lcleft;
        now->neighbour[1] = edt->lcright;
        edt->lcleft = now;
        // 2.1 更新另一个光标
        if(edt->rcright == edt->lcright){
            edt->rcleft = now;
        }
        // 更新光标区间的大小
        if(edt->LC_RC < 0){
            edt->LC_RC -= 1;
        }
    }
    // 右光标
    else {
        // 连接新节点
        edt->rcleft->neighbour[1] = now;
        edt->rcright->neighbour[0] = now;
        now->neighbour[0] = edt->rcleft;
        now->neighbour[1] = edt->rcright;
        edt->rcleft = now;
        // 2.2 更新另一个光标
        if(edt->lcright == edt->rcright){
            edt->lcleft = now;
        }
        // 更新光标区间的大小
        if(edt->LC_RC > 0){
            edt->LC_RC += 1;
        }
    }
    //
    edt->counter += 1;
    return 1;
}

int Delete(LIST *edt, char cursor){
    if(cursor == 'L'){
        if(edt->lcright == &(edt->tail))return 0;
        // 更新光标右侧
        edt->lcright = edt->lcright->neighbour[1];
        edt->lcleft->neighbour[1]=edt->lcright;
        edt->lcright->neighbour[0]=edt->lcleft;
        // 1.1 更新另一个光标
        if(edt->rcleft == edt->lcleft){
            edt->rcright = edt->lcright;
        }
        else if(edt->rcright == edt->lcright){
            edt->rcleft = edt->lcleft;
        }
        // 更新光标区间的大小
        if(edt->LC_RC > 0){
            edt->LC_RC -= 1;
        }
    }
    else {
        if(edt->rcright == &(edt->tail))return 0;
        // 更新光标右侧
        edt->rcright = edt->rcright->neighbour[1];
        edt->rcleft->neighbour[1]=edt->rcright;
        edt->rcright->neighbour[0]=edt->rcleft;
        // 1.2 更新另一个光标
        if(edt->lcleft == edt->rcleft){
            edt->lcright = edt->rcright;
        }
        else if(edt->lcright == edt->rcright){
            edt->lcleft = edt->rcleft;
        }
        // 更新光标区间的大小
        if(edt->LC_RC < 0){
            edt->LC_RC += 1;
        }
    }
    //
    edt->counter -= 1;

    return 1;
}

int Reverse(LIST *edt){
    if(edt->LC_RC < 1)return 0;
    // 暴力反转
    NODE *l = edt->lcright, *r = edt->rcleft;
    int cnt = (edt->LC_RC)/2;
    while(cnt--){
        int t=l->c; l->c = r->c; r->c = t;
        l=l->neighbour[1];
        r=r->neighbour[0];
    }
    return 1;
}

int Show(LIST *edt){
    NODE *now = edt->head.neighbour[1];
    //NODE *End = &(edt->tail);
    int dir = 1;
    int counter = edt->counter;
    while( counter-- > 0 && now){
        printf("%c", now->c);
        now = now->neighbour[dir];
    }
    puts("");
    return 1;
}



char s[MAXN],op[2],cursor[2],c[2];
int n, Case=2;

signed main()
{
    //freopen("out.out","w",stdout);

    scanf("%s",s);
    Init(&editor,s);
    scanf("%d",&n);
    while(n--){
        scanf("%s",op);
        //Show(&editor);printf("%d::%s\n",++Case,op);
        if(op[0] == '<'){
            scanf("%s",cursor);
            puts( MoveLeft(&editor,cursor[0]) ? "T" : "F");
        }
        else if(op[0] == '>'){
            scanf("%s",cursor);
            puts( MoveRight(&editor,cursor[0]) ? "T" : "F");
        }
        else if(op[0] == 'I'){
            scanf("%s%s",cursor,c);
            puts( Insert(&editor,cursor[0],c[0]) ? "T" : "F");
        }
        else if(op[0] == 'D'){
            scanf("%s",cursor);
            puts( Delete(&editor,cursor[0]) ? "T" : "F");
        }
        else if(op[0] == 'R'){
            puts( Reverse(&editor) ? "T" : "F");
        }
        else if(op[0] == 'S'){
            Show(&editor);
        }
        else {
            //puts("The testcase is wrong.");
        }
        //Show(&editor);debug(&editor);
    }

    return 0;
}



/*




*/
