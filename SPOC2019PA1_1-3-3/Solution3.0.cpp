/*
Author: Snickeen.
Email : ff@snickeen.com
Date  : 2019.07.11 Thu.

If you find out any bugs, please tell me. Thank you.
*/

#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

#define MAXN (4000006)

/******************************************************/



/*  //////////////////////////////////////////////////

维护两个list，一个正序一个逆序，这样可以O(1)截取完成reverse

begin:
    >>> >>>>> >
    < <<<<< <<<
end:
    >>> <<<<< >
    < >>>>> <<<

/////////////////////////////////////////////////// */



/// -------------------------------->>>>>>>>>>>>>>>>>>>>>>> ///
// List

struct NODE{
    char c;
    struct NODE *pred, *succ;
    NODE(char _c=0, struct NODE* pre=NULL, struct NODE* post=NULL){
        c = _c;
        pred = pre;
        succ = post;
    }
    ~NODE(){}
};
struct CURSOR{
    struct NODE *forerunner, *successor;
    CURSOR(){forerunner = successor = NULL;}
};

struct LIST{
    NODE head,tail;  // 首尾节点
    CURSOR leftcursor,rightcursor; //左右光标
    int range, counter;

    LIST(){
        head.succ = &tail;
        tail.pred = &head;
        leftcursor.forerunner = &head;
        leftcursor.successor = &tail;
        rightcursor = leftcursor;
        range = counter = 0;
    }
    ~LIST(){}

    // 初始化，其实可以省略用在右光标插入的姿势代替
    void Init(char s[]){
        int len = strlen(s);
        NODE *pre = &head, *post = &tail;
        for(int i=0;i<len;i++){
            NODE *now = new NODE(s[i],pre,post);
            pre->succ = now;
            post->pred= now;
            pre=now;
        }
        leftcursor.successor = head.succ;
        rightcursor.forerunner = tail.pred;
        range = counter = len;
    }

    // 左移
    void _moveleft(CURSOR &a){
        a.successor = a.forerunner;
        a.forerunner = a.forerunner->pred;
    }
    char MoveLeft(char cursor){
        if(cursor == 'L'){
            if(leftcursor.forerunner == &head)return 0;
            _moveleft(leftcursor);
            range++;
        }
        else {
            if(rightcursor.forerunner == &head)return 0;
            _moveleft(rightcursor);
            range--;
        }
        return 1;
    }

    // 右移
    void _moveright(CURSOR &a){
        a.forerunner = a.successor;
        a.successor = a.successor->succ;
    }
    char MoveRight(char cursor){
        if(cursor == 'L'){
            if(leftcursor.successor == &tail)return 0;
            _moveright(leftcursor);
            range--;
        }
        else {
            if(rightcursor.successor == &tail)return 0;
            _moveright(rightcursor);
            range++;
        }
        return 1;
    }

    // 在光标左侧插入节点
    void _insert(CURSOR &a, CURSOR &b, char c){
        NODE *now = new NODE(c, a.forerunner, a.successor);
        a.forerunner->succ = now;
        a.successor->pred = now;
        // 更新当前光标
        a.forerunner = now;
        // 更新另一个光标
        if(b.successor == a.successor)b=a;
    }
    char Insert(char cursor, char c){
        //if(c<33||c>126){cout<<"Something is wrong.\n";return 0;}
        if(cursor == 'L'){
            _insert(leftcursor, rightcursor, c);
            if(range < 0)range--; // 更新光标中间段大小
        }
        else {
            _insert(rightcursor, leftcursor, c);
            if(range > 0)range++; // 更新光标中间段大小
        }
        counter++;  // 更新链表的节点总个数
        return 1;
    }

    // 在光标右侧删除节点
    void _delete(CURSOR &a,CURSOR &b){
        NODE *p = a.successor;
        // 更新光标右侧
        a.successor = a.successor->succ;
        // 更新节点的链接
        a.forerunner->succ = a.successor;
        a.successor->pred = a.forerunner;
        // 更新另一个光标
        if(b.forerunner == a.forerunner || b.successor == a.successor) b = a;
        delete p;
    }
    char Delete(char cursor){
        if(cursor == 'L'){
            if(leftcursor.successor == &tail)return 0;
            _delete(leftcursor,rightcursor); //
            if(range > 0)range--; // 更新光标中间段大小
        }
        else {
            if(rightcursor.successor == &tail)return 0;
            _delete(rightcursor,leftcursor); //
            if(range < 0)range++; // 更新光标中间段大小
        }
        counter--; // 更新链表长度的计数器
        return 1;
    }

    // 反转操作，在后面的class editor里面，两个list来维护reverse
    //char _Reverse(){}

    // 显示文本串
    void Show(){
        NODE *now = head.succ;
        int cnt = counter;
        while(cnt-- > 0){
            cout<<(char)(now->c);
            now = now->succ;
        }
        cout<<"\n";
    }

    //
    void debug(){
        cout<<"---------------------------"<<endl;
        cout<<(&head)<<" "<<(&tail)<<endl;
        cout<<leftcursor.forerunner<<" "<<leftcursor.successor<<" "
            <<rightcursor.forerunner<<" "<<rightcursor.successor<<endl;
        cout<<range<<" "<<counter<<endl;

        NODE *now = head.succ;
        int cnt = counter, tmp;
        if(now == leftcursor.successor)cout<<'[';
        if(now == rightcursor.successor)cout<<']';
        while(cnt-- > 0){
            cout<<(char)(now->c);
            now = now->succ;
            if(now == leftcursor.successor)cout<<'[';
            if(now == rightcursor.successor)cout<<']';
        }
        cout<<endl;
        cout<<"===========================\n\n"<<endl;
    }

};



struct EDITOR{
    LIST answer, revans;
    EDITOR(){}
    ~EDITOR(){}


    // 初始化，其实可以省略用在右光标插入的姿势代替
    void Init(char s[]){
        answer.Init(s);
        int len = strlen(s);
        for(int l=0,r=len-1;l<r;l++,r--){swap(s[l],s[r]);}
        revans.Init(s);
        // 这样逆序的俩光标和正序的俩对应，只是单个光标的左右相反
        swap(revans.leftcursor, revans.rightcursor);
        revans.range = -revans.range;
        // 如果上面两行不使用的话，正序的{lf,ls,rf,rs}对应逆序的{rs,rf,ls,lf}，lr表示左右光标，fs表示前驱后继
        // 当然如果不用的这两行的话，后面有些地方需要改，关于光标的地方
    }
    // 左移
    char MoveLeft(char cursor){
        if(!answer.MoveLeft(cursor))return 0;
        revans.MoveRight(cursor);
        return 1;
    }
    // 右移
    char MoveRight(char cursor){
        if(!answer.MoveRight(cursor))return 0;
        revans.MoveLeft(cursor);
        return 1;
    }
    // 在光标左侧插入节点
    char Insert(char cursor, char c){
        answer.Insert(cursor,c);
        revans.Insert(cursor,c);
        // 非常关键的光标的更新！！！
        if(answer.range != 0){
            revans.MoveLeft(cursor);
        }
        else {
            revans.MoveLeft('L');
            revans.MoveLeft('R');
        }
        return 1;
    }
    // 在光标右侧删除节点
    char Delete(char cursor){
        if(!answer.Delete(cursor))return 0;
        revans.MoveLeft(cursor);
        revans.Delete(cursor);
        return 1;
    }
    // 反转
    char Reverse(){
        if(answer.range < 1)return 0;
        if(answer.range == 1)return 1;
        // 更新链表的连接
        swap(answer.leftcursor.forerunner->succ, revans.rightcursor.forerunner->succ);
        swap(answer.leftcursor.successor->pred, revans.rightcursor.successor->pred);
        swap(answer.rightcursor.forerunner->succ,revans.leftcursor.forerunner->succ);
        swap(answer.rightcursor.successor->pred,revans.leftcursor.successor->pred);
        // 更新光标的左右
        answer.leftcursor.successor = answer.leftcursor.forerunner->succ;
        answer.rightcursor.forerunner = answer.rightcursor.successor->pred;
        revans.leftcursor.forerunner = revans.leftcursor.successor->pred;
        revans.rightcursor.successor = revans.rightcursor.forerunner->succ;
        return 1;
    }

    void Show(){
        answer.Show();
    }
    void debug(){
        answer.debug();
        revans.debug();
    }
};

// Editior
/// <<<<<<<<<<<<<<<<<<<<<<<<<--------------------------------------- ///

EDITOR editor;

char s[MAXN],op,cursor='-',c='-';
int n, res;

signed main()
{
    //freopen("out.out","w",stdout);
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //cout<<sizeof(editor)<<" "<<sizeof(editor.answer)<<endl;
    //cout<<sizeof(editor.answer.head)<<" "<<sizeof(editor.answer.leftcursor)<<endl;
    //96 48  12 8

    cin >> s;
    editor.Init(s);
    //editor.debug();
    cin >> n;
    while(n--){
        cin >> op;
        if(op == '<'){
            cin >> cursor;
            res = editor.MoveLeft(cursor);
        }
        else if(op == '>'){
            cin >> cursor;
            res = editor.MoveRight(cursor);
        }
        else if(op == 'I'){
            cin >> cursor >> c;
            res = editor.Insert(cursor,c);
        }
        else if(op == 'D'){
            cin >> cursor;
            res = editor.Delete(cursor);
        }
        else if(op == 'R'){
            res = editor.Reverse();
        }
        else if(op == 'S'){
            editor.Show();
            res = -1;
        }
        //else {cout<<("The testcase is wrong.");}
        if(res==0)cout<<"F\n";
        if(res==1)cout<<"T\n";

        //cout<<op<<" "<<cursor<<" "<<c<<endl;cursor='-',c='-';
        //editor.debug();
    }

    return 0;
}



/* testcase 1.

abcdefg
23
S
R
S
I R A
S
R
S
I R B
S
R
S
I R C
S
R
S
< R
> L
R
S
< R
> L
R
S

*/


/* testcase 2.




abcdefghijk
33
R
R
S
< R
S
I R T
< R
> L
< L
S
I R Y
R
S
R
< R
> L
I L I
< R
R
> L
I L E
I R K
D R
S
< L
S
D L
> L
I L V
D R
< L
> L
S


*/

