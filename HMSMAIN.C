#include<stdio.h>
#include<HM1.h>
int main()
{
    do
    {
        printf("\n********Menu********\n\n1.Add patient records\n2.View available records\n3.Search patient by ID, name, disease, age, Doctor name.\n4.Edit records\n5.Delete patients record\n6.Exit ");
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
            Add_patient_records();
            break;
       /* case 2:
            View_available_records();
            break;
        case 3:
            Search_patient();
            break;
            case 4:Edit_records();
                break;
            case 5:Delete_patients_record();
                break;
        default:
            break;*/
        }
    }  while (choise != 6);
}