#include "RBST.hpp"
/***********************************************************/
/******************* PROVIDED FUNCTIONS ********************/
/***********************************************************/

int RBST::add(const Key& key, bool verbose) {
    unsigned int oldSize = m_size;
    m_head = randomAdd(m_head, key);
    if (m_size > oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is added into the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is already in the tree."<<endl;
        }
        return 0;
    }
    if (verbose) cout<<endl;
};

int RBST::del(const Key& key, bool verbose) {
    unsigned oldSize= m_size;
    m_head = del(m_head, key);
    if (m_size < oldSize) {
        if (verbose) {
            cout<<"Node "<<key<< " is deleted from the tree."<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    }
};

int RBST::find(const Key& key, bool verbose) {
    RBSTNode* ret = find(m_head, key);
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<< " is not in the tree."<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<<"Node "<<key<< " is in the tree."<<endl;
        }
        return 1;
    }
};

int RBST::dump(char sep) {
    int ret = dump(m_head, sep);
    cout<<"SIZE: " <<ret<<endl;
    return ret;
};

int RBST::dump(RBSTNode* target, char sep) {
    if (target == NULL) {
        return 0;
    }
    int ret = dump(target->left(), sep);
    cout<< *target<<sep;
    ret ++;
    ret += dump(target->right(), sep);
    return ret;
};



/***********************************************************/
/****************  FUNCTIONS TO BE COMPLETED  ***************/
/***********************************************************/


/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

RBSTNode*  RBST::rightRotate(RBSTNode* target) {
    ////////////// Write your code below  ////////////////////////
	RBSTNode *newRoot, *rightChild;
	newRoot = rightChild = NULL;
	
	//If it doesn't have a right child, tough luck.. Can't rotate!
	if(!target->right())
		return NULL;
	newRoot = target->right();
	rightChild = newRoot->left();
	
	newRoot->setLeft(target);
	target->setRight(rightChild);
	
    return newRoot;
};

RBSTNode*  RBST::leftRotate(RBSTNode* target) {
    ////////////// Write your code below  ////////////////////////
	RBSTNode *newRoot, *leftChild;
	newRoot = leftChild = NULL;
	
	//If it doesn't have a left child, tough luck.. Can't rotate!
	if(!target->left())
		return NULL;
	newRoot = target->left();
	leftChild = newRoot->right();
	
	newRoot->setRight(target);
	target->setLeft(leftChild);
	
    return newRoot;
};

RBSTNode* RBST::addRoot(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////
	if(target == NULL)
		return target;
	if(key < *target) {
		target->setLeft(addRoot(target->left(), key));
		return rightRotate(target);
	}
	target->setRight(addRoot(target->right(), key));
	return leftRotate(target);
};


RBSTNode* RBST::randomAdd(RBSTNode* target, const Key& key) {
    countAdd++;
    ////////////// Write your code below  ////////////////////////
	//Arrived to the end of the recursion:
	if(target == NULL) {
		++m_size;
		return target;
	}
	int r = rand() % m_size + 1;
	if(r == 1) {
		++m_size;
		return addRoot(target, key);
	} 
	if(key < *target)
		target->setLeft(randomAdd(target->left(), key));
	 target->setRight(randomAdd(target->right(), key));
	 return target;
};


/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////

RBSTNode* RBST::find(RBSTNode* target, const Key& key) {
    countFind++;
    if(target == NULL || *target == key)
		return target;
	if(*target > key)
		return find(target->right(), key); 
    return find(target->left(), key);
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////


RBSTNode* RBST::del(RBSTNode* target, const Key& key) {
    countDelete++;
    ////////////// Write your code below  ////////////////////////
	if(target == NULL) {
		--m_size;
		return NULL;
	}
	if(key < *target) {
		target->setLeft(del(target->left(), key));
		return target;
	} else if(key > *target) {
		target->setRight(del(target->right(), key));
		return target;
	} 
	RBSTNode* temp;
	
	if(!target->left()) {
		temp = target->right();
		delete target;
		target = temp;
		--m_size;
	} else if(!target->right()) {
		temp = target->left();
		delete target;
		target = temp;
		--m_size;
	} else {
		temp = target->right();
		while(temp->left()) {
			temp = temp->left();
		}
		target->setRight(del(target->right(), *temp));
	}
    return target;
};

