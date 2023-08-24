#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
int age, cabinNo, choise;
char patientname[20], doctorname[20], disease[20], patient_gender[7], patient_blood_group[4], adminname[20], patient_phone[10], patient_id[10];
char search_field[20];
char search_query[100];
int found = 0;
char found_filename[100];
int is_valid_blood_group(const char *blood_group)
{
    return strcmp(blood_group, "A") == 0 || strcmp(blood_group, "B") == 0 ||
           strcmp(blood_group, "AB") == 0 || strcmp(blood_group, "O") == 0 ||
           strcmp(blood_group, "-A") == 0 || strcmp(blood_group, "-B") == 0 ||
           strcmp(blood_group, "-AB") == 0 || strcmp(blood_group, "-O") == 0;
}
int is_valid_phone_number(const char *phone)
{
    size_t len = strlen(phone);
    if (len != 10)
    {
        return 0;
    }
    for (size_t i = 0; i < len; i++)
    {
        if (!isdigit(phone[i]))
        {
            return 0;
        }
    }
    return 1;
}
void Add_patient_records()
{
    printf("Enter the user name: ");
    fflush(stdin);
    fgets(adminname, sizeof(adminname), stdin);
    printf("Enter the patient name: ");
    fflush(stdin);
    fgets(patientname, sizeof(patientname), stdin);
    printf("Enter the patient id: ");
    fflush(stdin);
    fgets(patient_id, sizeof(patient_id), stdin);
    while (1)
    {
        printf("Enter the patient age: ");
        if (scanf("%d", &age) != 1 || age <= 0)
        {
            printf("Invalid age. Please enter a valid positive age.\n");
            while (getchar() != '\n')
                ;
        }
        else
        {
            break;
        }
    }
    while (1)
    {
        printf("Enter the patient gender (Male/Female/Others): ");
        scanf(" %s", patient_gender);

        for (int i = 0; patient_gender[i]; i++)
        {
            patient_gender[i] = tolower(patient_gender[i]);
        }

        if (strcmp(patient_gender, "male") == 0 || strcmp(patient_gender, "female") == 0 || strcmp(patient_gender, "others") == 0)
        {
            break;
        }
        else
        {
            printf("Invalid gender. Please enter a valid gender (Male/Female/Others).\n");
        }
    }
    while (1)
    {
        printf("Enter the patient phone number: ");
        scanf("%s", patient_phone);

        if (is_valid_phone_number(patient_phone))
        {
            break;
        }
        else
        {
            printf("Invalid phone number. Please enter a valid 10-digit phone number.\n");
        }
    }
    while (1)
    {
        printf("Enter the patient blood group (A/B/AB/O or -A/-B/-AB/-O): ");
        scanf("%s", patient_blood_group);
        for (int i = 0; patient_blood_group[i]; i++)
        {
            patient_blood_group[i] = toupper(patient_blood_group[i]);
        }

        if (is_valid_blood_group(patient_blood_group))
        {
            break;
        }
        else
        {
            printf("Invalid blood group. Please enter a valid blood group (A/B/AB/O or -A/-B/-AB/-O).\n");
        }
    }
    printf("Enter name of the disease: ");
    fflush(stdin);
    fgets(disease, sizeof(disease), stdin);
    printf("Enter the name of the doctor who is handeling the patient: ");
    fflush(stdin);
    fgets(doctorname, sizeof(doctorname), stdin);
    printf("Enter the cabin number");
    scanf("%d", &cabinNo);
    while (1)
    {
        printf("\nPlease review the entered data:\n");
        printf("Patient ID: %s\n", patient_id);
        printf("User Name: %s\n", adminname);
        printf("Patient Name: %s\n", patientname);
        printf("Patient Age: %d\n", age);
        printf("Patient Gender: %s\n", patient_gender);
        printf("Blood Group: %s\n", patient_blood_group);
        printf("Phone Number: %s\n", patient_phone);
        printf("Patient Disease: %s\n", disease);
        printf("Doctor Handling Patient: %s\n", doctorname);
        printf("Cabin Number: %d\n", cabinNo);

        printf("\nIs the data correct and you want to save? (yes/no): ");
        char confirmation[10];
        scanf("%s", confirmation);

        if (strcmp(confirmation, "yes") == 0)
        {
            char file_name[100];
            printf("Enter the file name to save the data: ");
            scanf("%s", file_name);

            FILE *file = fopen(file_name, "a");
            if (file == NULL)
            {
                printf("Error opening file for writing.\n");
                return;
            }
            fprintf(file, "-----------------------------------\n");
            fprintf(file, "Patient ID: %s\n", patient_id);
            fprintf(file, "User Name: %s\n", adminname);
            fprintf(file, "Patient Name: %s\n", patientname);
            fprintf(file, "Patient Age: %d\n", age);
            fprintf(file, "Patient Gender: %s\n", patient_gender);
            fprintf(file, "Blood Group: %s\n", patient_blood_group);
            fprintf(file, "Phone Number: %s\n", patient_phone);
            fprintf(file, "Patient Disease: %s\n", disease);
            fprintf(file, "Doctor Handling Patient: %s\n", doctorname);
            fprintf(file, "Cabin Number: %d\n", cabinNo);
            fprintf(file, "-----------------------------------\n");

            fclose(file);
            printf("\nData has been saved to the file.\n");
            break;
        }

        else if (strcmp(confirmation, "no") == 0)
        {
            printf("Data is incorrect. Please edit the necessary fields.\n");
            int edit_choice;
            do
            {
                printf("Which field would you like to edit?\n");
                printf("1. User Name\n");
                printf("2. Patient Name\n");
                printf("3. Patient Age\n");
                printf("4. Patient Gender\n");
                printf("5. Blood Group\n");
                printf("6. Phone Number\n");
                printf("7. Patient Disease\n");
                printf("8. Doctor Handling Patient\n");
                printf("9. Cabin Number\n");
                printf("10. Patient ID\n");
                printf("0. Done editing\n");

                scanf("%d", &edit_choice);

                switch (edit_choice)
                {
                case 1:
                    printf("Enter corrected User Name: ");
                    fflush(stdin);
                    fgets(adminname, sizeof(adminname), stdin);
                    break;
                case 2:
                    printf("Enter corrected Patient Name: ");
                    fflush(stdin);
                    fgets(patientname, sizeof(patientname), stdin);
                    break;
                case 3:
                    while (1)
                    {
                        printf("Enter corrected Patient Age: ");
                        if (scanf("%d", &age) != 1 || age <= 0)
                        {
                            printf("Invalid age. Please enter a valid positive age.\n");
                            while (getchar() != '\n')
                                ;
                        }
                        else
                        {
                            break;
                        }
                    }
                    break;
                case 4:
                    while (1)
                    {
                        printf("Enter corrected Patient Gender (Male/Female/Others): ");
                        scanf(" %s", patient_gender);

                        for (int i = 0; patient_gender[i]; i++)
                        {
                            patient_gender[i] = tolower(patient_gender[i]);
                        }

                        if (strcmp(patient_gender, "male") == 0 || strcmp(patient_gender, "female") == 0 || strcmp(patient_gender, "others") == 0)
                        {
                            break;
                        }
                        else
                        {
                            printf("Invalid gender. Please enter a valid gender (Male/Female/Others).\n");
                        }
                    }
                    break;
                case 5:
                    while (1)
                    {
                        printf("Enter corrected Blood Group (A/B/AB/O or -A/-B/-AB/-O): ");
                        scanf(" %s", patient_blood_group);
                        for (int i = 0; patient_blood_group[i]; i++)
                        {
                            patient_blood_group[i] = toupper(patient_blood_group[i]);
                        }

                        if (is_valid_blood_group(patient_blood_group))
                        {
                            break;
                        }
                        else
                        {
                            printf("Invalid blood group. Please enter a valid blood group (A/B/AB/O or -A/-B/-AB/-O).\n");
                        }
                    }
                    break;
                case 6:
                    while (1)
                    {
                        printf("Enter corrected Phone Number: ");
                        scanf("%s", patient_phone);

                        if (is_valid_phone_number(patient_phone))
                        {
                            break;
                        }
                        else
                        {
                            printf("Invalid phone number. Please enter a valid 10-digit phone number.\n");
                        }
                    }
                    break;
                case 7:
                    printf("Enter corrected Patient Disease: ");
                    fflush(stdin);
                    fgets(disease, sizeof(disease), stdin);
                    break;
                case 8:
                    printf("Enter corrected Doctor Handling Patient: ");
                    fflush(stdin);
                    fgets(doctorname, sizeof(doctorname), stdin);
                    break;
                case 9:
                    printf("Enter corrected Cabin Number: ");
                    scanf("%d", &cabinNo);
                    break;
                case 10:
                    printf("Enter corrected Patient ID: ");
                    scanf("%s", patient_id);
                    break;
                case 0:
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
                    break;
                }
            } while (edit_choice != 0);
        }

        else
        {
            printf("Invalid input. Please enter 'yes' or 'no'.\n");
        }
    }
}
