#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int revenue_of_shop[1000];
int custumer_shop[1000][1000];
typedef struct period
{
    char timer[10];
    int val;
}period;

period a[200000+10];

int hash(char* inp){
    int n = strlen(inp), temp = 0;
    for(int i = 0 ; i < n ; i++)
        if( '0' <= inp[i] && inp[i] <= '9')
            temp = temp*10 + inp[i] - '0';
    return temp%1000;
}

int cmp(const period* TimePoint1,const period* TimePoint2){
    return strcmp(TimePoint1->timer, TimePoint2->timer);
}




int main(){
    freopen("analizesale.inp", "r", stdin);

    int number_orders = 0, revenue = 0;

    while(1){
        char C[10], P[10], SHOP[10], time[10];
        int price;
        scanf("%s", C);
        if(strcmp(C, "#") == 0)
            break;
        scanf("%s %d %s %s", P, &price, SHOP, time);
        int h = hash(SHOP);
        strcpy(a[number_orders].timer, time);
        a[number_orders].val = price;
        custumer_shop[hash(C)][h] += price;
        revenue_of_shop[h] += price;
        number_orders++;
        revenue = revenue + price;
    }

    qsort(a, number_orders, sizeof(period), cmp);

    while (1){
        char cmd[100];
        scanf("%s", cmd);
        if(strcmp(cmd, "#") == 0)
            break;
        else if(strcmp(cmd, "?total_number_orders") == 0)
            printf("%d\n", number_orders);
        else if(strcmp(cmd, "?total_revenue") == 0)
            printf("%d\n", revenue);
        else if(strcmp(cmd, "?revenue_of_shop") == 0){
            char SHOP[10];
            scanf("%s", SHOP);
            printf("%d\n", revenue_of_shop[hash(SHOP)]);
        }
        else if(strcmp(cmd, "?total_consume_of_customer_shop") == 0){
            char C[10], SHOP[10];
            scanf("%s%s", C, SHOP);
            printf("%d\n", custumer_shop[hash(C)][hash(SHOP)]);
        }
        else if(strcmp(cmd, "?total_revenue_in_period") == 0){
            char S[10], E[10];
            scanf("%s%s", S, E);
            int summ = 0;
            for(int i = 0; i < number_orders && strcmp(a[i].timer, E) <= 0 ; i++){
                if(strcmp(a[i].timer, S) >= 0)
                    summ += a[i].val;
            }
            printf("%d\n", summ);
        }
        
    }
    return 0;
}
