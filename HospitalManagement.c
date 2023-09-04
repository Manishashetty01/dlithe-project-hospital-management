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
void View_available_records()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    printf("Available patient records:\n");

    int record_count = 0;
    char record_files[100][256];

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            if (strstr(entry->d_name, ".txt") != NULL)
            {
                printf("%d. %s\n", record_count + 1, entry->d_name);
                strcpy(record_files[record_count], entry->d_name);
                record_count++;
            }
        }
    }

    if (record_count == 0)
    {
        printf("No patient records found.\n");
        closedir(dir);
        return;
    }

    int chosen_record;
    do
    {
        printf("Choose a record to view (1-%d) or 0 to cancel: ", record_count);
        scanf("%d", &chosen_record);
        if (chosen_record < 0 || chosen_record > record_count)
        {
            printf("Invalid choice. Please enter a valid option.\n");
        }
        else if (chosen_record == 0)
        {
            closedir(dir);
            return;
        }
    } while (chosen_record < 0 || chosen_record > record_count);

    printf("You chose to view record: %s\n", record_files[chosen_record - 1]);

    char file_to_open[256];
    strcpy(file_to_open, record_files[chosen_record - 1]);

    FILE *file = fopen(file_to_open, "r");
    if (file == NULL)
    {
        printf("Error opening file for viewing.\n");
        closedir(dir);
        return;
    }

    printf("Content of the record:\n");

    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    fclose(file);

    closedir(dir);
}

void Search_patient()
{
    printf("Enter the search field (name/age/doctor/disease/id): ");
    scanf("%s", search_field);

    printf("Enter the search query: ");
    fflush(stdin);
    fgets(search_query, sizeof(search_query), stdin);

    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error opening directory.\n");
        return;
    }

    printf("\nMatching records:\n");

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            FILE *file = fopen(entry->d_name, "r");
            if (file != NULL)
            {
                char line[200];
                while (fgets(line, sizeof(line), file))
                {
                    if (strstr(line, search_query) != NULL)
                    {
                        found++;
                        printf("File: %s\n", entry->d_name);
                        strcpy(found_filename, entry->d_name);
                        break;
                    }
                }
                fclose(file);
            }
        }
    }

    closedir(dir);

    if (found == 0)
    {
        printf("No files found containing the search query.\n");
    }
    else if (found == 1)
    {
        printf("Do you want to open the found file? (yes/no): ");
        char open_choice[10];
        scanf("%s", open_choice);
        if (strcmp(open_choice, "yes") == 0)
        {
            FILE *found_file = fopen(found_filename, "r");
            if (found_file != NULL)
            {
                char line[200];
                while (fgets(line, sizeof(line), found_file))
                {
                    printf("%s", line);
                }
                fclose(found_file);
            }
            else
            {
                printf("Error opening file.\n");
            }
        }
    }
    else if (found > 1)
    {
        while (found > 1)
        {
            printf("Multiple matching records found. Enter another field to narrow down the search:\n");
            printf("Enter the new search field (name/age/doctor/disease/id): ");
            scanf("%s", search_field);

            printf("Enter the new search query: ");
            fflush(stdin);
            fgets(search_query, sizeof(search_query), stdin);
            found = 0;

            dir = opendir(".");
            if (dir == NULL)
            {
                printf("Error opening directory.\n");
                return;
            }

            printf("\nMatching records:\n");

            while ((entry = readdir(dir)) != NULL)
            {
                if (entry->d_type == DT_REG)
                {
                    FILE *file = fopen(entry->d_name, "r");
                    if (file != NULL)
                    {
                        char line[200];
                        while (fgets(line, sizeof(line), file))
                        {
                            if (strstr(line, search_query) != NULL)
                            {
                                found++;
                                printf("File: %s\n", entry->d_name);
                                strcpy(found_filename, entry->d_name);
                                break;
                            }
                        }
                        fclose(file);
                    }
                }
            }

            closedir(dir);
        }

        printf("Do you want to open any of the found files? (yes/no): ");
        char open_choice[10];
        scanf("%s", open_choice);
        if (strcmp(open_choice, "yes") == 0)
        {
            FILE *found_file = fopen(found_filename, "r");
            if (found_file != NULL)
            {
                char line[200];
                while (fgets(line, sizeof(line), found_file))
                {
                    printf("%s", line);
                }
                fclose(found_file);
            }
            else
            {
                printf("Error opening file.\n");
            }
        }
    }
}

void Edit_records()
{
    printf("Enter the name of the file to edit: ");
    char file_to_edit[256];
    scanf("%s", file_to_edit);

    FILE *file = fopen(file_to_edit, "r");
    if (file == NULL)
    {
        printf("Error opening the file for editing.\n");
        return;
    }

    char temp_file_name[256];
    strcpy(temp_file_name, "temp.txt");
    FILE *temp_file = fopen(temp_file_name, "w");
    if (temp_file == NULL)
    {
        printf("Error creating a temporary file.\n");
        fclose(file);
        return;
    }

    char line[200];
    int found = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "Patient ID:") != NULL)
        {
            printf("Current content of the record:\n");
            found = 1;
        }

        if (found)
        {
            fputs(line, stdout);  // Display the current line
            if (strstr(line, "Cabin Number:") != NULL)
            {
                break;  // Stop displaying after Cabin Number
            }
        }
    }

    if (!found)
    {
        printf("Record not found or has invalid format.\n");
        fclose(file);
        fclose(temp_file);
        remove(temp_file_name);  // Remove the temporary file
        return;
    }

    int edit_choice;
    printf("\nWhich field would you like to edit?\n");
    printf("1. User Name\n");
    printf("2. Patient Name\n");
    printf("3. Patient Age\n");
    printf("4. Patient Gender\n");
    printf("5. Blood Group\n");
    printf("6. Phone Number\n");
    printf("7. Patient Disease\n");
    printf("8. Doctor Handling Patient\n");
    printf("9. Cabin Number\n");
    printf("0. Exit editing\n");

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
                    while (getchar() != '\n');
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
        case 0:
            break;
        default:
            printf("Invalid choice. No changes made.\n");
            fclose(file);
            fclose(temp_file);
            remove(temp_file_name);  // Remove the temporary file
            return;
    }

    // Reopen the original file for reading
    fclose(file);
    file = fopen(file_to_edit, "r");
    if (file == NULL)
    {
        printf("Error opening the file for reading.\n");
        fclose(temp_file);
        remove(temp_file_name);  // Remove the temporary file
        return;
    }

    // Copy the contents of the original file to the temporary file with edits
    found = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "Patient ID:") != NULL)
        {
            found = 1;
        }

        if (found)
        {
            switch (edit_choice)
            {
                case 1:
                    if (strstr(line, "User Name:") != NULL)
                    {
                        fprintf(temp_file, "User Name: %s", adminname);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                case 2:
                    if (strstr(line, "Patient Name:") != NULL)
                    {
                        fprintf(temp_file, "Patient Name: %s", patientname);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                case 3:
                    if (strstr(line, "Patient Age:") != NULL)
                    {
                        fprintf(temp_file, "Patient Age: %d\n", age);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                case 4:
                    if (strstr(line, "Patient Gender:") != NULL)
                    {
                        fprintf(temp_file, "Patient Gender: %s", patient_gender);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                case 5:
                    if (strstr(line, "Blood Group:") != NULL)
                    {
                        fprintf(temp_file, "Blood Group: %s", patient_blood_group);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                case 6:
                    if (strstr(line, "Phone Number:") != NULL)
                    {
                        fprintf(temp_file, "Phone Number: %s", patient_phone);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                case 7:
                    if (strstr(line, "Patient Disease:") != NULL)
                    {
                        fprintf(temp_file, "Patient Disease: %s", disease);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                case 8:
                    if (strstr(line, "Doctor Handling Patient:") != NULL)
                    {
                        fprintf(temp_file, "Doctor Handling Patient: %s", doctorname);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                case 9:
                    if (strstr(line, "Cabin Number:") != NULL)
                    {
                        fprintf(temp_file, "Cabin Number: %d\n", cabinNo);
                    }
                    else
                    {
                        fputs(line, temp_file);
                    }
                    break;
                default:
                    fputs(line, temp_file);
            }

            if (strstr(line, "Cabin Number:") != NULL)
            {
                break;
            }
        }
        else
        {
            fputs(line, temp_file);
        }
    }

    // Close both files
    fclose(file);
    fclose(temp_file);

    // Replace the original file with the temporary file
    if (remove(file_to_edit) == 0)
    {
        if (rename(temp_file_name, file_to_edit) == 0)
        {
            printf("Data has been successfully edited and saved to the file.\n");
        }
        else
        {
            printf("Error renaming the temporary file.\n");
        }
    }
    else
    {
        printf("Error deleting the original file.\n");
    }
}

void Delete_patients_record()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error opening directory.\n");
        return;
    }

    printf("Available patient records for deletion:\n");

    int record_count = 0;
    char record_files[100][256];

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            if (strstr(entry->d_name, ".txt") != NULL)
            {
                printf("%d. %s\n", record_count + 1, entry->d_name);
                strcpy(record_files[record_count], entry->d_name);
                record_count++;
            }
        }
    }

    if (record_count == 0)
    {
        printf("No patient records found for deletion.\n");
        closedir(dir);
        return;
    }

    int chosen_record;
    do
    {
        printf("Choose a record to delete (1-%d) or 0 to cancel: ", record_count);
        scanf("%d", &chosen_record);
        if (chosen_record < 0 || chosen_record > record_count)
        {
            printf("Invalid choice. Please enter a valid option.\n");
        }
        else if (chosen_record == 0)
        {
            closedir(dir);
            return;
        }
    } while (chosen_record < 0 || chosen_record > record_count);

    printf("You chose to delete record: %s\n", record_files[chosen_record - 1]);

    char file_to_delete[256];
    strcpy(file_to_delete, record_files[chosen_record - 1]);

    if (remove(file_to_delete) == 0)
    {
        printf("Record deleted successfully!\n");
    }
    else
    {
        printf("Error deleting the record.\n");
    }

    closedir(dir);
}

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
        case 2:
            View_available_records();
            break;
        case 3:
            Search_patient();
            break;
        case 4:
            Edit_records();
            break;
        case 5:
            Delete_patients_record();
            break;
        default:
            break;
        }
    } while (choise != 6);
}