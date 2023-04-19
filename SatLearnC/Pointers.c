# include <stdio.h>
//*i matlab jo value "i"  ke andar hai. 
//&i matlab i ka address;  "i" varaible computer ke jis address par hai.  
int AssignValueToAnotherVariableUsingPointer() {
    int age = 22;
    int *ptr = &age;
    int _age = *ptr;

    printf("%d", _age);
    return 0;
}


/*int main() {
    int age = 19;
    int *ptr = &age;
    int _age = *ptr;

    printf("%d", _age);
    return 0;
}*/

/*int main() {
    int age = 23;
    int *ptr = &age;
    int _age = *ptr;

    printf("%d", _age);
    return 0;
}*/

int UnderStandPointer()
{
    int a = 10;
    int *ptr;  ///pointer declaration
    ptr = &a;  ///initialization
    ///int *ptr = &a;  /// declaration and initialization
    printf("Value of a is : %d",a);
    printf("\naddress of a is : %d",&a);
    printf("\nValue of ptr is : %d",ptr);
    printf("\nValue of *ptr is : %d",*ptr);
    printf("\nValue of *(&a) is : %d",*(&a));
    return 0;
}

int UsePointersToStoreArray()
{
  int a = 10, b = 2;
  int arr[]={10,20,34,45,56,67,8,9,6};
  int *p1,*p2;
  p1=arr;
  printf("\n%d",*p1);
  printf("\nAddress is : %d",p1);

  p1--;//pointer arithematics 
       //question: Are you getting the results that you want. 
  printf("\n%d",*p1);
  printf("\nAddress is %d",p1);

  p1=p1+2; ////pointer arithmatics 
  printf("\n%d",*p1);
  printf("\nAddress is : %d",p1);
  return 0;
}

int PointerArithmatics()
{
    int a = 10, b = 20;
    int arr[]={10,20,30,40,5,6,7,8,9};
    int* p1;// , * p2;
    p1=arr;
    printf("\n%d",*p1);
    printf("\nAddress is : %d",p1);
    ++p1;
    printf("\n%d",*p1);
    printf("\nAddress is : %d",p1);
    p1--;
    printf("\n%d",*p1);
    printf("\nAddress is : %d",p1);
    p1 = p1+2;
    printf("\n%d",*p1);
    printf("\nAddress is : %d",p1);
    return 0;
}

void swap(int* x, int* y)
{
  int t;
  t = *x;
  *x = *y;
  *y = t;
  printf("value in called function %d %d \n", *x, *y);
}

int QuestionOnPointerArithmatics()
{
  int a = 10, b = 2;
  int arr[] = { 10,20,34,45,56,67,8,9,6 };
  printf("\n%d", *(arr));
  printf("\n%d", *(arr + 1));
  printf("\n%d", *(arr + 2));

  //Question:First guess what it will print. Then uncomment the following code and see if your guess was correct.   
  //printf("\n%d", *(arr + 5));
  //printf("\n%d", *(arr + 7));
  
  //Question: Have you used sizeof() before? 
  // First guess what it will print. Then uncomment the following code and see if your guess was correct.   
  //printf("\nSize of arr = %d \n", sizeof(arr));
  return 0;
}

int main()
{
  //AssignValueToAnotherVariableUsingPointer();
  //UnderStandPointer();
  //UsePointersToStoreArray();
  //PointerArithmatics();
  QuestionOnPointerArithmatics();
  
  //int a=10, b=20;
  //printf("%d %d before swap\n",a, b);
  //swap(&a, &b);
  //printf("\n %d %d after swap",a, b);
}

