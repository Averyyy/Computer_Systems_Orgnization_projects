#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


void add ( bst_node ** root, char * word ) {
  if (*root == NULL) {
      (*root) -> data = word;
  }
 if (strcmp(word, (*root)->data)<0){
    add(&((*root)->left), word);}
  else{
    add(&((*root)->right), word);
    }


}

 
void inorder ( bst_node * root ) {
    if (root != NULL) {
    inorder(root->left);
    printf("%s -> ", root->data);
    inorder(root->right);
  }

}


 
char * removeSmallest (  bst_node ** root ){
    struct bst_node * temp;
    if((*root)!=NULL){
        while((*root)->left->left!=NULL)
            (*root)=(*root)->left;
            
        if((*root)->left->right!=NULL)
        {
            temp=(*root)->left;
            (*root)->left=(*root)->left->right;
            free(temp);
        }else{
            free((*root)->left->left);
            char *result = (*root)->left;
            (*root)->left = NULL;
            return *result;
        }
        
    }else{
      return NULL;
    }
}

 
char * removeLargest (  bst_node ** root ){
    
    if ((*root) == NULL) return NULL;
	  bst_node *temp = *root;
    bst_node *prev = NULL;
    while (temp->right != NULL) {
      prev = temp;
      temp = temp->right;
    }
	
    if (prev == NULL) {
      (*root) = (*root)->left; }
    else 
    { char *result = prev->right->data;
      prev->right = NULL;
      return result;
      } 
    
}




