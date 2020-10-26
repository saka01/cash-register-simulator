#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
int countOfLinesFromFile(char *filename){
FILE* myfile = fopen(filename, "r");
int ch, number_of_lines = 0;
do
{
    ch = fgetc(myfile);
    if(ch == '\n')
        number_of_lines++;
}
while (ch != EOF);
if(ch != '\n' && number_of_lines != 0)
    number_of_lines++;
fclose(myfile);
  return number_of_lines-1;
}

int main() {

  printf("*******************BEGINNING*******************\n");

  FILE *dailytransactions;
  char* file1 = "C:\\Users\\mosho\\Desktop\\FINAL EXAMINATION\\DailyTransactions.txt";
  dailytransactions = fopen(file1, "r");

  FILE *codenameprice;
  char* file2 = "C:\\Users\\mosho\\Desktop\\FINAL EXAMINATION\\CodeNamePrice.txt";
  codenameprice = fopen(file2, "r");

  FILE *categoryname;
  char* file3 = "C:\\Users\\mosho\\Desktop\\FINAL EXAMINATION\\CategoryName.txt";
  categoryname = fopen(file3, "r");



  struct Categories{
    float CategoryPrice;
    int CategoryCode;
    int CategorySales;
    char CategoryName[16];
    struct Categories* nextCategory;
  };

  struct CodeNamePrice{
    int ItemCode;
    char ItemName[16];
    float ItemPrice;
    struct CodeNamePrice* nextCodeNamePrice;
  };

  struct DailyTransactions{
      int ItemCode;
      int NumItems;
      struct DailyTransactions* nextTransaction;
  };

  struct ItemStruct{
      int ReceiptNum;
      int ItemCode;
      int NumItems;
      float ItemPrice;
      float TotSales;
      char ItemName[15];
      int Totals;
      struct ItemStruct* nextItem;
  };

 if(dailytransactions == NULL){
      printf("Could not open file DataTransactions.txt");
      exit(1);
  }else if(codenameprice == NULL){
      printf("Could not open file CodeNamePrice.txt");
      exit(1);
  }else if(categoryname == NULL){
      printf("Could not open file CategoryName.txt");
      exit(1);
  }

struct ItemStruct customer[50];
struct CodeNamePrice inventory[50];
struct Categories category[50];
struct DailyTransactions dailytransaction[50];


int d = countOfLinesFromFile(file2);
printf("%d\n", d);

//Scans CodeNamePrice file to Data structure
int pos = 0;
while(pos<d){
fscanf(codenameprice,"%d %15[^\n] %f",&inventory[pos].ItemCode, &inventory[pos].ItemName, &inventory[pos].ItemPrice);
printf("\nInventory[%d]: %d %s %.2f", pos, inventory[pos].ItemCode,  inventory[pos].ItemName, inventory[pos].ItemPrice);
pos++;
}

int m = countOfLinesFromFile(file3);
printf("%d\n", m);

//Scans CategoryCode and Name to Data Structure
int post = 0;
while(post<m){
  fscanf(categoryname,"%d %[^\n]s",&category[post].CategoryCode, &category[post].CategoryName);
  printf("\nCategories: %d %s", category[post].CategoryCode,  category[post].CategoryName);
  post++;
}

int n = countOfLinesFromFile(file1);
printf("%d\n", n);

//Scans dailytransactions to Data Structure
int p = 0;
while(1){
  fscanf(dailytransactions,"%d %d", &customer[p].ItemCode, &customer[p].NumItems);
  printf("\nDaily transactions: %d %d", customer[p].ItemCode,  customer[p].NumItems); //Printing to Console for my help
  if (customer[p].ItemCode == 000) {
    printf("*****************************End of Customer 1************************");
    break;
  }
  p++;
}



//Sorting the item Codes
int a;
for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n-1; ++j){
        if (customer[i].ItemCode > customer[j].ItemCode){
            a =  customer[i].ItemCode;
            customer[i].ItemCode = customer[j].ItemCode;
            customer[j].ItemCode = a;
                }
            }
        }



  FILE *receipt;
     /* open the file for writing*/
     receipt = fopen ("C:\\Users\\mosho\\Desktop\\FINAL EXAMINATION\\receipts.txt","w");

     fprintf (receipt, "Code\t\t\t\t\t Item Name\t\t\t\t\t\t Price\t\t\t\t\t NumItem\t TotSale\n");


int itemcount = 0;
float totalsales = 0.00;


for(int j = 0; j < d; j++){
  for(int i = 0; i < d; i++){
    customer[j].TotSales = (inventory[i].ItemPrice)*(customer[j].NumItems);


    if(customer[j].ItemCode == inventory[i].ItemCode){
      totalsales += customer[j].TotSales;
      itemcount += customer[j].NumItems;
        printf("Item Code: %d\n",customer[j].ItemCode);
        fprintf (receipt, "%d",customer[j].ItemCode);

        fprintf (receipt, "\t\t\t\t\t\t\t");

        printf("Item Name: %s\n",inventory[i].ItemName);
        fprintf (receipt, "%s",inventory[i].ItemName);

        fprintf (receipt, "\t\t\t");

        printf("Item Price: %.2f\n",inventory[i].ItemPrice);
        fprintf (receipt, "%.2f",inventory[i].ItemPrice);

        fprintf (receipt, "\t\t\t\t\t\t\t\t");

        printf("Num of Items: %d\n",customer[j].NumItems);
        fprintf (receipt, "%d",customer[j].NumItems);

        fprintf (receipt, "\t\t\t");

        printf("Total Sales for %s : %.2f\n",inventory[i].ItemName,customer[j].TotSales);
        fprintf (receipt, "%.2f\n",customer[j].TotSales);

    }
  }
}
printf("\n");
printf("Total num of items: %d\n",itemcount);
fprintf (receipt, "\n");
fprintf (receipt, "\t\t\t\t\t\t\t\t\t\t\t\t\t\tTotals:\t\t\t\t\t\t\t\t\t\t\t%d\t\t\t\t%.2f",itemcount,totalsales);

// printf("Total: %.2f\n",totalsales);
// fprintf (receipt, "%.2f\n",totalsales);




FILE *summary;

   /* open the file for writing*/
   summary = fopen ("C:\\Users\\mosho\\Desktop\\FINAL EXAMINATION\\Daily Summary Report.txt","w");

   fprintf (summary, "Code\t\t\t\t\t Category Name\t\t\t\t\t\t Items Sold\t\t\t\t\t TotSales Amt\n");

int cate[8] = {0};
// int cate2 = 0;
// int cate3 = 0;
// int cate4 = 0;
// int cate5 = 0;
// int cate6 = 0;
// int cate7 = 0;
// int cate8 = 0;

int coun = 0;

for(int i = 0; i<n-1;i++){

  int detcat = (customer[i].ItemCode/100)-1;
  customer[i].TotSales = (inventory[i].ItemPrice)*(customer[i+1].NumItems);

  printf("%.2f\n",customer[i].TotSales);

    if(detcat == 0){
    printf("category 1\n");
    cate[0] += 1;
    }else if(detcat == 1){
    printf("category 2\n");
    cate[1] += 1;

    }else if(detcat == 2){
    printf("category 3\n");
    cate[2] += 1;

    }else if(detcat == 3){
    printf("category 4\n");
    cate[3] += 1;

    }else if(detcat == 4){
    printf("category 5\n");
    cate[4] += 1;

    }else if(detcat == 5){
    printf("category 6\n");
    cate[5] += 1;

    }else if(detcat == 6){
    printf("category 7\n");
    cate[6] += 1;

    }else if(detcat == 7){
    printf("category 8\n");
    cate[7] += 1;
    }
  }

printf("Category 100 sold: %d\n",cate[0] );
printf("Category 200 sold: %d\n",cate[1] );
printf("Category 300 sold: %d\n",cate[2] );
printf("Category 400 sold: %d\n",cate[3] );
printf("Category 500 sold: %d\n",cate[4] );
printf("Category 600 sold: %d\n",cate[5] );
printf("Category 700 sold: %d\n",cate[6] );
printf("Category 800 sold: %d\n",cate[7] );

int y = 0;
for(int i = 0; i<n-1; i++){
category[i].CategorySales = cate[i];
}

for(int i = 0; i<m; i++){
  printf("\nCategories: %d %s", category[i].CategoryCode,  category[i].CategoryName);
  fprintf (summary, "%d",category[i].CategoryCode);
  fprintf (summary, "\t\t\t\t\t\t\t\t");
  fprintf (summary, "%s",category[i].CategoryName);
  fprintf (summary, "\t\t\t\t\t\t\t\t");
  fprintf (summary, "%d\n", category[i].CategorySales);


  }
  fprintf(summary, "Total Customers : 1\n");
  fprintf(summary, "Total Items Sold: %d\n",itemcount);
  fprintf(summary, "Total Sales: %.2f \n",totalsales);




 printf("\nClosing the files...") ;
 fclose(dailytransactions);
 fclose(codenameprice);
 fclose(categoryname);
 /* close the file*/
 fclose (receipt);
 fclose (summary);

  return 0;
}
