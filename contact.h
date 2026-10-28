/* Name : E.krishnaveni
   File name : contact.h
   Date : 17-06-2026
   Description : structure definition and function declarations for Address Book 
*/
#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>

// Structures for the Fields
struct Contacts
{
    char Name[50];
    char Mobile_number[11];
    char Mail_ID[50];
};
/* Function declarations for Address Book operations */
void create_contact(struct Contacts *,int *);
int list_contacts(struct Contacts *,int *);
int search_contacts(struct  Contacts*,int *);
int edit_contact(struct Contacts *,int *,int);
int delete_contact(struct Contacts *,int *);
int save_contact(struct Contacts *,int *);
int valid_name(struct Contacts *,char *,int *);
int valid_phonenumber(struct Contacts *,char *,int *);
int valid_email(struct Contacts *,char *,int *);
#endif
// CONTACT_H