/* Name : E.krishnaveni
File name : contact.c
Date : 17-06-2026
Description : Contains all contact management functions such as create, edit, delete, search, display, save, and validation.
*/
#include "contact.h"
#include <ctype.h>
#include <string.h>
/*Function defintion to create a new contact*/
void create_contact(struct Contacts *contact_details, int *contact_count)
{
    while (1)
    {
        // Create a new contact name
        printf("Enter the Name: ");
        scanf("%s", contact_details[*(contact_count)].Name);                                  // read the name from the user
        if (valid_name(contact_details, contact_details[*contact_count].Name, contact_count)) // function call to validate name
        {
            break;
        }
        else
        {
            printf("Name must contains ALphabets only\n");
        }
    }
    while (1)
    {
        printf("Enter the Phonenumber: ");
        scanf("%s", contact_details[*(contact_count)].Mobile_number);                                                 // Read the phone number from the user
        int res = (valid_phonenumber(contact_details, contact_details[*contact_count].Mobile_number, contact_count)); // Function call to validate phone number
        if (res == 1)
        {
            break;
        }
        else if (res == -1)
        {
            printf("Number must contains 10 digits\n");
        }
        else if (res == -2)
        {
            printf("Number must contains only digits\n");
        }
        else if (res == 0)
        {
            printf("Number already exit try another number\n");
        }
    }
    while (1)
    {
        printf("Enter the Email: ");                                                                      // creating new email id
        scanf("%s", contact_details[*(contact_count)].Mail_ID);                                           // creating new email id
        int res = (valid_email(contact_details, contact_details[*contact_count].Mail_ID, contact_count)); // Function call to validate email
        if (res == 1)
        {
            break;
        }
        else if (res == -1)
        {
            printf("Dont include Uppercase in mail\n");
        }
        else if (res == -2)
        {
            printf("Entered @ and .com more than once\n");
        }
        else if (res == 0)
        {
            printf("Mail already exist\n");
        }
        else if (res == -3)
        {
            printf("Email must contains @ and .com\n");
        }
        else if (res == -4)
        {
            printf("You entered @ or .com only\n");
        }
        else if (res == -5)
        {
            printf("Invalid Email\n");
        }
    }
    (*contact_count)++; // Increment the contact count after successful contact creation
    printf("Contact created successfully\n");
}
/* Function definition to save contacts*/
int save_contact(struct Contacts *contact_details, int *contact_count)
{
    FILE *fptr;
    fptr = fopen("list.txt", "w");            // Open the file in write mode to write the contact list
    fprintf(fptr, "#%d\n", *(contact_count)); // writing contact count to file list.txt
    for (int i = 0; i < *contact_count; i++)  // Write all valid contacts to the file
    {
        if (contact_details[i].Name[0] != '\0')
        {
            fprintf(fptr, "%s,%s,%s\n", contact_details[i].Name, contact_details[i].Mobile_number, contact_details[i].Mail_ID); // Write all valid contacts to the file
        }
    }
    fclose(fptr); // closing  list.txt file
    printf("Saved\n");
    return 0;
}
/* Function definition to list all contacts*/
int list_contacts(struct Contacts *contact_details, int *contact_count)
{
    int j = 1;
    for (int i = 0; i < *contact_count; i++)
    {
        if (contact_details[i].Name[0] != '\0')
        {
            printf("%d     %-30s %-18s %-18s\n", j, contact_details[i].Name, contact_details[i].Mobile_number, contact_details[i].Mail_ID); // to display all contact list
            j++;
        }
    }
    return 0;
}
/* Function declaration to edit the contact*/
int edit_contact(struct Contacts *contact_details, int *contact_count, int found)
{
    int option;
    scanf("%d", &option); // reading option from user
    switch (option)
    {
    case 1: // Select the field to edit
    {
        char name[20];
        printf("Enter the name to Edit: ");
        scanf("%s", name);
        int index = 0, res = 1, count = 0;
        for (int i = 0; i < *(contact_count); i++) // Search for the entered name in the contact list
        {
            int flag = 0;
            int res = strcmp(contact_details[i].Name, name); // Search for the entered name in the contact list
            if (res == 0)
            {
                flag = 1;
                index = i;
            }
            if (flag)
            {
                printf("%s   %s   %s\n", contact_details[index].Name, contact_details[index].Mobile_number, contact_details[index].Mail_ID); // print the contact list with similar name if count>1
                count++;
            }
        }
        if (count == 0)
        {
            printf("Name not found\n");
        }
        else if (count == 1) // Edit the contact if only one matching name is found
        {
            char name[20];
            while (1)
            {
                printf("Enter the new name to edit: ");
                scanf("%s", name);
                if (valid_name(contact_details, name, contact_count)) // checking valid name or not
                {
                    break;
                }
                else
                {
                    printf("Name must contains ALphabets only\n");
                }
            }
            strcpy(contact_details[index].Name, name); // copy the new name into the existing name
            printf("Edited successfully\n");
        }
        else if (count > 1)
        {
            printf("Name found more than once:\n"); // if name found more than once
            printf("Enter the number or mail:\n");
            printf("1.Mobile Number\n");
            printf("2.Email\n");
            printf("Enter the option:\n");
            int opt;
            scanf("%d", &opt);
            if (opt == 1)
            {
                char number[11];
                printf("Enter the number to edit the name:\n");
                scanf("%s", number);
                int index = -1, res = -1;
                for (int i = 0; i < *(contact_count); i++)
                {
                    res = strcmp(contact_details[i].Mobile_number, number); // Search for the matching mobile number
                    if (res == 0)
                    {
                        index = i;
                        break;
                    }
                }
                if (res != 0)
                {
                    printf("Number not found\n");
                }
                else if (res == 0)
                {
                    while (1)
                    {
                        printf("Enter the new name to edit:\n");
                        char name[20];
                        scanf("%s", name);
                        int res1 = valid_name(contact_details, name, contact_count);
                        if (res1 == 1)
                        {
                            strcpy(contact_details[index].Name, name); // copy new name into the existing name
                            printf("Name edited successfully\n");
                            break;
                        }
                        else
                        {
                            printf("Name must contains ALphabets only\n");
                        }
                    }
                }
                else
                {
                    printf("Number not found\n");
                }
            }
            else if (opt == 2)
            {
                char email[60];
                printf("Enter the email to edit the name:\n");
                scanf("%s", email);
                int index = -1, res = -1;
                for (int i = 0; i < *(contact_count); i++)
                {
                    res = strcmp(contact_details[i].Mail_ID, email); // Search for the matching email id
                    if (res == 0)
                    {
                        index = i;
                        break;
                    }
                }
                if (res != 0)
                {
                    printf("mail not found\n");
                }
                else if (res == 0)
                {
                    while (1)
                    {
                        printf("Enter the new name to edit:\n");
                        char name[20];
                        scanf("%s", name);
                        int res1 = valid_name(contact_details, name, contact_count); // Function call validate name
                        if (res1 == 1)
                        {
                            strcpy(contact_details[index].Name, name); // if name validated succesfully copy new name into existing name
                            printf("Name edited successfully\n");
                            break;
                        }
                        else
                        {
                            printf("Name must contains ALphabets only\n");
                        }
                    }
                }
                else
                {
                    printf("Mail not found\n");
                }
            }
        }
    }
        return 0;
    case 2:
    {
        char mobile[11];
        printf("Enter the number to Edit: ");
        scanf("%s", mobile);
        int flag = 0, index = -1;
        for (int i = 0; i < *(contact_count); i++)
        {
            int res = strcmp(contact_details[i].Mobile_number, mobile); // Search for the entered phone number
            if (res == 0)
            {
                flag = 1;
                index = i;
                break;
            }
        }
        if (flag)
        {
            char number[11];
            while (1)
            {
                printf("Enter the new number to edit: ");
                scanf("%s", number);
                int res = (valid_phonenumber(contact_details, number, contact_count)); // function call to validate phone number
                if (res == 1)
                {
                    break;
                }
                else if (res == -1)
                {
                    printf("Number must contains 10 digits\n");
                }
                else if (res == -2)
                {
                    printf("Number must contains only digits\n");
                }
                else if (res == 0)
                {
                    printf("Number already exit try another number\n");
                }
            }
            strcpy(contact_details[index].Mobile_number, number); // if number successfully validated copy new number into the previous number
            printf("Edited successfully\n");
        }
        else
        {
            printf("Number not found\n");
        }
        return 0;
    case 3:
    {
        char email[20];
        printf("Enter the email to Edit: ");
        scanf("%s", email);
        int flag = 0, index = 0;
        for (int i = 0; i < *(contact_count); i++)
        {
            int res = strcmp(contact_details[i].Mail_ID, email);
            if (res == 0)
            {
                flag = 1;
                index = i;
                break;
            }
        }
        if (flag)
        {
            char emailid[20];
            while (1)
            {
                printf("Enter the new email to edit: ");
                scanf("%s", emailid);
                int res = valid_email(contact_details, emailid, contact_count); // function call to validate email
                if (res == 1)
                {
                    break;
                }
                else if (res == -1)
                {
                    printf("Dont include Uppercase in mail\n");
                }
                else if (res == -2)
                {
                    printf("Entered @ and .com more than once\n");
                }
                else if (res == 0)
                {
                    printf("Mail already exist\n");
                }
                else if (res == -3)
                {
                    printf("Email must contains @ and .com\n");
                }
                else if (res == -4)
                {
                    printf("You entered @ or .com only\n");
                }
                else if (res == -5)
                {
                    printf("Invalid Email\n");
                }
            }
            strcpy(contact_details[index].Mail_ID, emailid); // Copy the new email into the existing email field
            printf("\nEdited successfully");
        }
        else
        {
            printf("Email not found\n");
        }
    }
        return 0;
    }
    }
}
/* Function  defintion to delete the contact*/
int delete_contact(struct Contacts *contact_details, int *contact_count)
{
    int option;
    scanf("%d", &option);
    switch (option) // Select the contact deletion method
    {
    case 1:
    {
        char name[20];
        printf("Enter the name:\n");
        scanf("%s", name);
        int flag = 0, index = -1, count = 0;
        for (int i = 0; i < *(contact_count); i++) // Search for the entered name
        {
            int res = strcmp(contact_details[i].Name, name);
            if (res == 0)
            {
                count++;
                flag = 1;
                index = i;
            }
        }
        if (count == 0)
        {
            printf("Name not found\n");
        }
        else if (count == 1)
        {
            printf("Are you sure you want to delete");
            int option;
            printf("***select below option***\n");
            printf("1.yes\n");
            printf("2.No\n");
            scanf("%d", &option);
            if (option == 1)
            {
                contact_details[index].Name[0] = '\0'; // Clear all contact details to delete the contact
                contact_details[index].Mobile_number[0] = '\0';
                contact_details[index].Mail_ID[0] = '\0';
                printf("Contact deleted succesfully\n");
            }
            else
            {
                printf("Not deleted\n");
            }
        }

        else if (count > 1)
        {
            printf("Name found more than once:\n");
            printf("Enter the number or mail:\n");
            printf("1.Mobile Number\n");
            printf("2.Email\n");
            printf("Enter the option:\n");
            int opt;
            scanf("%d", &opt);
            int index = -1, res = -1;
            if (opt == 1)
            {
                char number[11];
                printf("Enter the number to delete the name:\n");
                scanf("%s", number);
                for (int i = 0; i < *(contact_count); i++)
                {
                    res = strcmp(contact_details[i].Mobile_number, number);
                    if (res == 0)
                    {
                        index = i;
                        break;
                    }
                }
                if (res != 0)
                {
                    printf("Number not found\n");
                }
                else if (res == 0)
                {
                    printf("Are you sure you want to delete");
                    int option;
                    printf("***select below option***\n");
                    printf("1.yes\n");
                    printf("2.No\n");
                    scanf("%d", &option);
                    if (option == 1)
                    {
                        contact_details[index].Name[0] = '\0';
                        contact_details[index].Mobile_number[0] = '\0';
                        contact_details[index].Mail_ID[0] = '\0';
                        printf("Contact deleted succesfully\n");
                    }
                    else
                    {
                        printf("Not deleted\n");
                    }
                }
            }
            else if (opt == 2)
            {
                char email[60];
                printf("Enter the email to edit the name:\n");
                scanf("%s", email);
                int index = -1, res = -1;
                for (int i = 0; i < *(contact_count); i++)
                {
                    res = strcmp(contact_details[i].Mail_ID, email);
                    if (res == 0)
                    {
                        index = i;
                        break;
                    }
                }
                if (res != 0)
                {
                    printf("mail not found\n");
                }
                else if (res == 0)
                {

                    printf("Are you sure you want to delete");
                    int option;
                    printf("***select below option***\n");
                    printf("1.yes\n");
                    printf("2.No\n");
                    scanf("%d", &option);
                    if (option == 1)
                    {
                        contact_details[index].Name[0] = '\0';
                        contact_details[index].Mobile_number[0] = '\0';
                        contact_details[index].Mail_ID[0] = '\0';
                        printf("Contact deleted succesfully\n");
                    }
                    else
                    {
                        printf("Not deleted\n");
                    }
                }
            }
        }
        return 0;
    }
    case 2:
    {
        char contact[20];
        printf("Enter the contact to delete:\n");
        scanf("%s", contact);
        int flag = 0, index = -1;
        for (int i = 0; i < *(contact_count); i++)
        {
            int res = strcmp(contact_details[i].Mobile_number, contact); // Search for the entered mobile number
            if (res == 0)
            {
                flag = 1;
                index = i;
                break;
            }
        }
        if (flag == 0)
        {
            printf("Number not found\n");
        }
        else if (flag)
        {
            printf("Are you sure you want to delete\n");
            int option;
            printf("select below option:\n");
            printf("1.yes\n 2.No\n");
            scanf("%d", &option);
            if (option == 1)
            {
                contact_details[index].Name[0] = '\0';
                contact_details[index].Mobile_number[0] = '\0'; // Clear all contact details to delete the contact
                contact_details[index].Mail_ID[0] = '\0';
                printf("Contact deleted succesfully\n");
            }
            else
            {
                printf("Not deleted\n");
            }
        }
        return 0;
    }
    case 3:
    {
        char email[20];
        printf("Enter the email to delete:\n");
        scanf("%s", email);
        int flag = 0, index = -1;
        for (int i = 0; i < *(contact_count); i++)
        {
            int res = strcmp(contact_details[i].Mail_ID, email); // Search for the entered email address
            if (res == 0)
            {
                flag = 1;
                index = i;
                break;
            }
        }
        if(flag==0)
        {
            printf("Email not found\n");
        }
        else if (flag)
        {
            printf("Are you sure you want to delete\n");
            int option;
            printf("***select below option***\n");
            printf("1.yes\n");
            printf("2.No\n");
            scanf("%d", &option);
            if (option == 1)
            {
                contact_details[index].Name[0] = '\0';
                contact_details[index].Mobile_number[0] = '\0'; // Clear all contact details to delete the contact
                contact_details[index].Mail_ID[0] = '\0';
                printf("Contact deleted succesfully\n");
            }
            else
            {
                printf("Not deleted\n");
            }
        }
    }
        return 0;
    }
}
/* Function definition to search contacts*/
int search_contacts(struct Contacts *contact_details, int *contact_count)
{
    int option;
    scanf("%d", &option);
    switch (option)
    {
    case 1:
    {
        char name[20];
        printf("Enter the name to search: ");
        scanf("%s", name);
        int flag = 0, index = 0, res = 1, found = 0;
        for (int i = 0; i < *(contact_count); i++)
        {
            int res = strcmp(contact_details[i].Name, name);
            if (res == 0)
            {
                found = 1;
                break;
            }
        }
        if (found) // Display all contacts with the matching name
        {
            for (int i = 0; i < *(contact_count); i++)
            {
                int flag = 0;
                int res = strcmp(contact_details[i].Name, name);
                if (res == 0)
                {
                    flag = 1;
                    index = i;
                }
                if (flag)
                {
                    printf("%s %s %s\n", contact_details[index].Name, contact_details[index].Mobile_number, contact_details[index].Mail_ID); // if name occurs more than once printing the contacts
                }
            }
        }
        else
        {
            printf("Name not found\n");
        }
        return 0;
    }
    case 2:
    {
        char mobile[11];
        printf("Enter the number to search: ");
        scanf("%s", mobile);
        int flag = 0, index = -1;
        for (int i = 0; i < *(contact_count); i++)
        {
            int res = strcmp(contact_details[i].Mobile_number, mobile);
            if (res == 0)
            {
                flag = 1;
                index = i;
                break;
            }
        }
        if (flag)
        {
            printf("%s %s %s", contact_details[index].Name, contact_details[index].Mobile_number, contact_details[index].Mail_ID);
        }
        else
        {
            printf("Number not found\n");
        }
        return 0;
    }
    case 3:
    {
        char email[20];
        printf("Enter the email to search: ");
        scanf("%s", email);
        int flag = 0, index = 0;
        for (int i = 0; i < *(contact_count); i++)
        {
            int res = strcmp(contact_details[i].Mail_ID, email);
            if (res == 0)
            {
                flag = 1;
                index = i;
                break;
            }
        }
        if (flag)
        {
            printf("%s %s %s", contact_details[index].Name, contact_details[index].Mobile_number, contact_details[index].Mail_ID);
        }
        else
        {
            printf("Email not found\n");
        }
        return 0;
    }
    }
}
// Function definiton to validate the name
int valid_name(struct Contacts *contact_details, char *Name, int *contact_count)
{
    int flag = 1;
    for (int i = 0; Name[i] != '\0'; i++)
    {
        if (!isalpha(Name[i]))
        {
            flag = 0;
            break;
        }
    }
    if (flag)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}
/* Function definiton to valid phone number*/
int valid_phonenumber(struct Contacts *contact_details, char *Mobile_number, int *contact_count)
{
    if (strlen(Mobile_number) != 10) // Check whether the phone number contains exactly 10 digits
    {
        return -1;
    }
    for (int i = 0; Mobile_number[i] != '\0'; i++)
    {
        if (!isdigit(Mobile_number[i]))
        {
            return -2;
        }
    }
    for (int i = 0; i < *(contact_count); i++) // Check whether the phone number already exists
    {
        int res = strcmp(contact_details[i].Mobile_number, Mobile_number);
        if (res == 0)
        {
            return 0;
        }
    }
    return 1;
}
// Function definition for validate the email
int valid_email(struct Contacts *contact_details, char *Mail_ID, int *contact_count)
{
    for (int i = 0; Mail_ID[i] != '\0'; i++)
    {
        if (Mail_ID[i] >= 65 && Mail_ID[i] <= 90)
        {
            return -1;
        }
    }
    int count = 0;
    for (int i = 0; Mail_ID[i] != '\0'; i++)
    {
        if (Mail_ID[i] == '\n')
        {
            Mail_ID[i] = '\0';
        }
    }
    for (int i = 0; Mail_ID[i] != '\0'; i++)
    {
        if (Mail_ID[i] == '@')
        {
            count = count + 1;
        }
    }
    char *ptr = strstr(Mail_ID, ".com");
    int found = 0;
    if (ptr != NULL)
    {
        found = 1;
        char *ptr1 = strstr(ptr + 4, ".com");
        if (ptr1 != NULL)
        {
            found = 2;
        }
    }
    if (((found == 1) && (count == 0)) || ((found == 0) && (count == 1)))
    {
        return -4;
    }
    if ((count == 0) || (found == 0))
    {
        return -3;
    }

    if ((count != 1) || (found != 1))
    {
        return -2;
    }
    for (int i = 0; i < *(contact_count); i++) // Check whether the email already exists
    {
        int res = strcmp(contact_details[i].Mail_ID, Mail_ID);
        if (res == 0)
        {
            return 0;
        }
    }
    char *ptr1 = strstr(Mail_ID, "@"); // Validate the position of '@' and ".com"
    char *ptr2 = strstr(Mail_ID, ".com");
    if ((ptr2 == ptr1 + 1) || (ptr2 < ptr1))
    {
        return -5;
    }
    else
    {
        return 1;
    }
    if ((count == 1) && (found == 1))
    {
        return 1;
    }
}
