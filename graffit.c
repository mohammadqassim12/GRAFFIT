/**
 * CSC A48 - Intro to Computer Science II, Summer 2021
 * 
 * Assignment 3 - Graffit
 * 
 * Graphs &
 * Recursion
 * Assignment
 * For
 * Freshmen
 * In
 * Toronto
 *
 * (I am so proud of that initialism.)
 * 
 * This is the program file where you will implement your solution for
 * Assignment 3. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will also need to have read the handout carefully. 
 * 
 * Parts where you have to implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive
 * and will check that your solution is *correct*, not only that it
 * provides functionality.
 * 
 * (c) 2020 William Song, Mustafa Quraish
 * (c) 2021 Charles Xu
 **/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3 // A small graph
#endif

typedef struct user_struct
{
  char name[MAX_STR_LEN];
  struct friend_node_struct *friends;
  struct brand_node_struct *brands;
  bool visited;
    struct friend_node_struct* userList;
} User;

typedef struct friend_node_struct
{
  User *user;
  struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct
{
  char brand_name[MAX_STR_LEN];
  struct brand_node_struct *next;
} BrandNode;

FriendNode *allUsers = NULL;

int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Given the head to a FriendNode linked list, returns true if a
 * given user's name exists in the list. Returns false otherwise.
 */
bool in_friend_list(FriendNode *head, User *node)
{
  for (FriendNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->user->name, node->name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a BrandNode linked list, returns true if a
 * given brand's name exists in the list. Returns false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name)
{
  for (BrandNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->brand_name, name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a FriendNode linked list, inserts a given user
 * into the linked list and returns the head of the new linked list.
 * The insertion is done in alphabetical order. If the user already
 * exists, no modifications are made and the list is returned as is.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (in_friend_list(head, node))
  {
    printf("User already in list\n");
    return head;
  }

  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->user->name, node->name) > 0)
  {
    fn->next = head;
    return fn;
  }

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a BrandNode linked list, inserts a given brand into
 * the linked list and returns the head of the new linked list. The
 * insertion is done in alphabetical order. If the brand already exists,
 * no modifications are made and the list is returned as is.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (in_brand_list(head, node))
  {
    printf("Brand already in list\n");
    return head;
  }

  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->brand_name, node) > 0)
  {
    fn->next = head;
    return fn;
  }

  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a FriendNode linked list, removes a given user from
 * the linked list and returns the head of the new linked list. If the user
 * does not exist, no modifications are made and the list is returned as is.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (!in_friend_list(head, node))
  {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0)
  {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given the head to a BrandNode linked list, removes a given brand from
 * the linked list and returns the head of the new linked list. If the brand
 * does not exist, no modifications are made and the list is returned as is.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (!in_brand_list(head, node))
  {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0)
  {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given a user, prints their name, friends, and liked brands.
 */
void print_user_data(User *user)
{
  printf("User name: %s\n", user->name);

  printf("Friends:\n");
  for (FriendNode *f = user->friends; f != NULL; f = f->next)
  {
    printf("   %s\n", f->user->name);
  }

  printf("Brands:\n");
  for (BrandNode *b = user->brands; b != NULL; b = b->next)
  {
    printf("   %s\n", b->brand_name);
  }
}

/**
 * Given a brand, returns the index of the brand inside the brand_names array.
 * If it doesn't exist in the array, return -1
 */
int get_brand_index(char *name)
{
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (strcmp(brand_names[i], name) == 0)
    {
      return i;
    }
  }

  printf("Brand '%s' not found\n", name);
  return -1; // Not found
}

/**
 * Given a brand, prints their name, index (inside the brand_names
 * array), and the names of other similar brands.
 */
void print_brand_data(char *brand_name)
{
  int idx = get_brand_index(brand_name);
  if (idx < 0)
  {
    printf("Brand '%s' not in the list.\n", brand_name);
    return;
  }

  printf("Brand name: %s\n", brand_name);
  printf("Brand idx: %d\n", idx);

  printf("Similar brands:\n");
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (brand_adjacency_matrix[idx][i] == 1 && strcmp(brand_names[i], "") != 0)
    {
      printf("   %s\n", brand_names[i]);
    }
  }
}

/**
 * Read from a given file and populate a the brand list and brand matrix.
 **/
void populate_brand_matrix(char *file_name)
{
  // Read the file
  char buff[MAX_STR_LEN];
  FILE *f = fopen(file_name, "r");
  fscanf(f, "%s", buff);
  char *line = buff;
  // Load up the brand_names matrix
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (i == MAT_SIZE - 1)
    {
      strcpy(brand_names[i], line);
      break;
    }
    int index = strchr(line, ',') - line;
    strncpy(brand_names[i], line, index);
    line = strchr(line, ',') + sizeof(char);
  }
  // Load up the brand_adjacency_matrix
  for (int x = 0; x < MAT_SIZE; x++)
  {
    fscanf(f, "%s", buff);
    for (int y = 0; y < MAT_SIZE; y++)
    {
      int value = (int)buff[y * 2];
      if (value == 48)
      {
        value = 0;
      }
      else
      {
        value = 1;
      }
      brand_adjacency_matrix[x][y] = value;
    }
  }
}

FriendNode *search_friend_list(FriendNode *head, User *node) {
    {
      for (FriendNode *cur = head; cur != NULL; cur = cur->next)
      {
        if (strcmp(cur->user->name, node->name) == 0)
        {
          return cur;
        }
      }
      return NULL;
    }
}

/**
 * TODO: Complete this function
 * Creates and returns a user.
 */
User *create_user(char *name)
{
        User *temp = (User *) calloc(1, sizeof(User));
        strcpy(temp ->name, name);
        temp -> friends = NULL;
        temp -> brands = NULL;
        temp -> visited = false;
        if (strcmp(name, "") == 0){
            free(temp);
            return NULL;
        }
        if (name == NULL){
            return NULL;
        }
        if (in_friend_list(allUsers, temp) == false)
            {
                allUsers = insert_into_friend_list(allUsers, temp);
                return temp;
            }
        
        free(temp);
      return NULL;
    }

/**
 * TODO: Complete this function
 * Deletes a given user.
 */
int delete_user(User *user)
{
    if(strcmp(user->name, "") == 0 || user == NULL){
        return -1;
      }
    if (in_friend_list(allUsers, user))
    {
        FriendNode *ji = allUsers;
        while(ji != NULL){
            if(in_friend_list( ji -> user -> friends,user)){
                ji -> user -> friends = delete_from_friend_list(ji-> user -> friends, user);
            }
            ji = ji -> next;
        }
        
        allUsers = delete_from_friend_list(allUsers, user);
        free(user);
        return 0;
    }
    return -1;
}


/**
 * TODO: Complete this function
 * Create a friendship between user and friend.
 */
int add_friend(User *user, User *friend)
{
    //empty string
    if(strcmp(user->name, "") == 0 || strcmp(friend->name, "") == 0){
        return -1;
      }
    // same user
    if(strcmp(user->name, friend->name) == 0){
        return -1;
      }
    // if users exists in gaffit
    if(in_friend_list(allUsers, user) == false || in_friend_list(allUsers, friend) == false){
      return -1;
    }
    // if friendship already exists
    if(in_friend_list(user->friends, friend) || in_friend_list(friend->friends, user)){
       return -1;
     }
    if (user != NULL && friend != NULL){
            user -> friends = insert_into_friend_list(user -> friends, friend);
            friend -> friends = insert_into_friend_list(friend -> friends, user);
            return 0;
    }
    return -1;
}

/**
 * TODO: Complete this function
 * Removes a friendship between user and friend.
 */
int remove_friend(User *user, User *friend)
{
    //empty string
    if(strcmp(user->name, "") == 0 || strcmp(friend->name, "") == 0){
        return -1;
      }
    // same user
    if(strcmp(user->name, friend->name) == 0 || user == friend){
        return -1;
      }
    // if users exists in gaffit
    if(in_friend_list(allUsers, user) == false || in_friend_list(allUsers, friend) == false){
      return -1;
    }
    // if friendship doesn't exists
    if(!in_friend_list(user->friends, friend) || !in_friend_list(friend->friends, user)){
       return -1;
     }
    if (user != NULL && friend != NULL){
        if (in_friend_list(user -> friends, friend) == true){
            user -> friends = delete_from_friend_list(user -> friends, friend);
            friend -> friends = delete_from_friend_list(friend -> friends, user);
            return 0;
        }
    }
    return -1;
}

/**
 * TODO: Complete this function
 * Creates a follow relationship, the user follows the brand.
 */
int follow_brand(User *user, char *brand_name)
{        if(!in_friend_list(allUsers, user)){
          return -1;
        }
        if(strcmp(user->name, "") == 0){
            return -1;
          }
        int index = get_brand_index(brand_name);
        if(index == -1){
          return -1;
        }
        if (user != NULL && brand_name != NULL){
            if(in_brand_list(user -> brands, brand_name) == false){
                user -> brands = insert_into_brand_list(user -> brands, brand_name);
                return 0;
            }
        }
      return -1;
    }
    


/**
 * TODO: Complete this function
 * Removes a follow relationship, the user unfollows the brand.
 */
int unfollow_brand(User *user, char *brand_name)
{
    if(strcmp(user->name, "") == 0){
        return -1;
      }
    int index = get_brand_index(brand_name);
    if(index == -1){
      return -1;
    }
    if(!in_friend_list(allUsers, user)){
        return -1;
      }
    if (user != NULL && brand_name != NULL){
        if(in_brand_list(user -> brands, brand_name)){
            user -> brands = delete_from_brand_list(user -> brands, brand_name);
            return 0;
        }
    }
  return -1;
}

/**
 * TODO: Complete this function
 * Return the number of mutual friends between two users.
 */
int get_mutual_friends(User *a, User *b)
{
    if(strcmp(a->name, "") == 0 || strcmp(b -> name, "") == 0 || !in_friend_list(allUsers, a) || !in_friend_list(allUsers, b) || a == NULL || b == NULL || a ==b){
        return 0;
      }
    int counter = 0;
    FriendNode *ptr = a -> friends;
    while(ptr != NULL){
        if(in_friend_list(b -> friends, ptr -> user)){
            counter++;
        }
        ptr = ptr -> next;
    }
  return counter;
}


/**
 * TODO: Complete this function
 * A degree of connection is the number of steps it takes to get from
 * one user to another. Returns a non-negative integer representing
 * the degrees of connection between two users.
 */
//void reset_visited(FriendNode *allUsers) {
//    for (FriendNode *ptr = allUsers; ptr != NULL; ptr = ptr->next) {
//        ptr->user->visited = false;
//    }
//}

int get_degrees_of_connection(User *a, User *b)
{
    if (a -> name == b -> name ){
        return 0;
    }
    FriendNode *ptr = allUsers;
    // making sure that all users(user -> visted) is false
    while(ptr != NULL){
      ptr->user->visited = false;
      ptr = ptr->next;
    }

    // check my friend list
    // visit first user himself
    a->visited = true;
    int degree = 1;

    FriendNode * ptr_2 =  insert_into_friend_list( NULL, a );
    FriendNode * new = NULL;
    do{
      new = NULL;
      while( ptr_2 != NULL ) {

        if( in_friend_list( ptr_2->user->friends, b) ) {
          return degree;
        }
        ptr_2->user->visited = true;

        FriendNode * friend_node = ptr_2->user->friends;
        while( friend_node != NULL ) {
          if( friend_node->user->visited != true ) {
            if(!in_friend_list(new,friend_node->user)){
              new = insert_into_friend_list(new, friend_node->user );
            }
          }
          friend_node = friend_node->next;
        }
        ptr_2 = ptr_2->next;
      }
      degree++;
      ptr_2 = new;
    }while ( new !=NULL );
    return -1;
}


/**
 * TODO: Complete this function
 * Marks two brands as similar.
 */
void connect_similar_brands(char *brandNameA, char *brandNameB)
{
    int brand_1 = get_brand_index(brandNameA);
    int brand_2 = get_brand_index(brandNameB);
    if (brand_1 != -1 && brand_2 != -1){
        brand_adjacency_matrix[brand_1][brand_2] = 1;
        brand_adjacency_matrix[brand_2][brand_1] = 1;
    }
  return;
}

/**
 * TODO: Complete this function
 * Marks two brands as not similar.
 */
void remove_similar_brands(char *brandNameA, char *brandNameB)
{
    int brand_1 = get_brand_index(brandNameA);
    int brand_2 = get_brand_index(brandNameB);
    if (brand_1 != -1 && brand_2 != -1){
        brand_adjacency_matrix[brand_1][brand_2] = 0;
        brand_adjacency_matrix[brand_2][brand_1] = 0;
    }
  return;
}
/**
 * TODO: Complete this function
 * Returns a suggested friend for the given user.
 */
int get_mutual_brands(User *a, User *b)
{
    int count = 0;
    BrandNode *ptr = a->brands;
    
    while (ptr != NULL) {
        if (in_brand_list(b->brands, ptr->brand_name) == true) count++;
        ptr = ptr->next;
    }
    
    return count;
}

User *get_suggested_friend(User *user)
{
    //check for last line in fxn description
    //special cases
    //start
    if (user == NULL){
        return NULL;
    }
    if (strcmp(user -> name, "") == 0){
        return NULL;
    }
    if(!in_friend_list(allUsers, user)){
       return NULL;
     }
    //end
    int common_brands = 0;
    FriendNode *ptr = allUsers;
    User* friend = NULL;
    while(ptr != NULL){
        if(!in_friend_list(user->friends, ptr->user) && strcmp(ptr->user->name, user->name) != 0){
            int counter = 0;
            BrandNode* ptr_2 = ptr->user->brands;
            while(ptr_2 != NULL){
                if(in_brand_list(user->brands, ptr_2->brand_name)){
                          counter++;
                        }
                        ptr_2 = ptr_2->next;
                      }
            if(friend == NULL){
                    friend = ptr->user;
                  }
            if(counter > common_brands){
                    common_brands = counter;
                    friend = ptr->user;
                  }
            else if(counter == common_brands){
                    if(strcmp(ptr->user->name, friend->name) > 0){
                      friend = ptr->user;
                    }
            }
    }
        ptr = ptr -> next;
    }
  return friend;
}

/**
 * TODO: Complete this function
 * Adds n suggested friends for the given user.
 * Returns how many friends were successfully followed.
 */
int add_suggested_friends(User *user, int n)
{
    if (user == NULL || strcmp(user->name, "") == 0 || in_friend_list(allUsers, user) == false || n <= 0) return 0;
    
    User *suggested == NULL;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        suggested = get_suggested_friend(user);
        if (suggested != NULL) {
            user->friends = insert_into_friend_list (user->friends, suggested);
            count++;
        }
    }
    return count;
}

/**
 * TODO: Complete this function
 * Follows n suggested brands for the given user.
 * Returns how many brands were successfully followed.
 */

int get_suggested_brand(User *user)
{
    int i, j, count, maxNum = 0, maxIndex = -1;;
    BrandNode *ptr;
    
    for (i = 0; i < MAT_SIZE; i++) {
        
       if (in_brand_list(user->brands, brand_names[i]) == false) {
            
            ptr = user->brands;
            count = 0;
            
            while (ptr != NULL) {
                j = get_brand_index(ptr->brand_name);
                
                if (brand_adjacency_matrix[i][j] == 1) count++;
                
                ptr = ptr->next;
            }
            
            if (count > maxNum || (count == maxNum && strcmp(brand_names[maxIndex], brand_names[i]) < 0)) {
                maxNum = count;
                maxIndex = i;
            }
        }
        
    }
    return maxIndex;
}

int follow_suggested_brands(User *user, int n)
{
    if (user == NULL || strcmp(user->name, "") == 0 || in_friend_list(allUsers, user) == false || n <= 0) return 0;
    
    int count = 0, suggested = -1;
    
    for (int i = 0; i < n; i++) {
        suggested = get_suggested_brand(user);
        if (suggested != -1) {
            user->brands = insert_into_brand_list (user->brands, brand_names[suggested]);
            count++;
        }
    }
    return count;
}
