 #include "SkipList.hpp"
/***********************************************************/
/********************** PROVIDED FUNCTIONS *****************/
/***********************************************************/
void SkipList::init(int maxHeight) {
    m_maxHeight = maxHeight;
    m_head = new SkipListNode("", m_maxHeight);
}

SkipList::~SkipList() {
    while (m_head != NULL) {
        SkipListNode* head = m_head;
        m_head = m_head->nextAtLevel(0);
        delete head;
    }
}

int SkipList::add(const Key& key, bool verbose) {
    if (find(key, false) != 0) {
        if (verbose) {
            cout<<"Node "<<key<<" is already in the list."<<endl;
        }
        return 0;
    }

    SkipListNode* newNode = new SkipListNode(key, randHeight());
    if (verbose) {
        cout<<"Add new node "<<*newNode<<" with height "<<newNode->height()<<endl;
    }
    int ret = add (m_head, newNode, m_maxHeight-1);
    if (ret == 0 ) {
        return ret;
    }
    return 1;
}

int SkipList::find(const Key &key, bool verbose) {
    SkipListNode* ret =find (m_head, key, m_maxHeight-1) ;
    if (ret == NULL) {
        if (verbose) {
            cout<< "Node "<<key<<" is not in the list"<<endl;
        }
        return 0;
    } else {
        if (verbose) {
            cout<< "Node "<<key<<" is in the list"<<endl;
        }
        return 1;
    }

}
int SkipList::del(const Key& key, bool verbose) {
    if (key.length() == 0){
      return 1;
    }
    SkipListNode* toBeDeleted  = del(m_head, key, m_maxHeight-1);

    if (toBeDeleted == NULL) {
        if (verbose) {
            cout<< "Node "<<key<<" is not in the list"<<endl;
        }
    } else {
        delete toBeDeleted;
        if (verbose) {
            cout<< "Node "<<key<<" is deleted from the list"<<endl;
        }
    }
    return 1;
}

void SkipList::dump(char sep) {
    int length = -1;
    cout<<"Current List: ";
    for ( SkipListNode* iter = m_head; (iter != NULL); iter=iter->nextAtLevel(0)) {
        length++;
        cout << string(*iter)<<" ";
        cout <<"("<< iter->height() <<":";
        unsigned int i;
        for (i=0; i< iter->height(); i++) {
            if (iter->nextAtLevel(i)) {
                cout<<" "<<i<<":"<<*(iter->nextAtLevel(i));
                cout.flush();
            }
        }
        cout<<")"<<sep;
    }
    cout<<length<<" nodes in total."<<endl;
}


/***********************************************************/
/***************  FUNCTIONS TO BE COMPLETED  ****************/
/***********************************************************/

/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

unsigned int SkipList::randHeight() {
    unsigned int t = rand();
    unsigned int j = 2;
    unsigned int i;
    for (i = 1; i < m_maxHeight; i++) {
        if (t > RAND_MAX / j) break;
        j = j + j;
    }
    return i;
}


int SkipList::add(SkipListNode* target, SkipListNode* newNode, unsigned int level) {
    if (target->nextAtLevel(level) != NULL &&
            (*target->nextAtLevel(level)) < *newNode) {
        countAdd++;
    }
    
    SkipListNode* t = target->nextAtLevel(level);
    // We found the position to add the newNode
    if (t == NULL || *newNode < *t) {
      // Adds the newNode to the current level
      if (level < newNode->height()) {
		    newNode->setNextAtLevel(level, t);
		    target->setNextAtLevel(level, newNode);
		  }
		  
		  // Adds the newNode to the next level
		  if (level > 0)
			  add(target, newNode, level-1);
	    
	    return 1;
	  }
    
    return add(t, newNode, level); 
}

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::find(SkipListNode* target, const Key& key, unsigned int level) {
    if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
        countFind++;
    }
 
    // We have finished searching the entire list
    if (target == NULL) 
        return NULL;
 
    // We found it! Yey!
    if (*target == key) 
        return target;
        
    SkipListNode* t = target->nextAtLevel(level);
    
    // the node we are searching is 
    // not in the current level
    if(t == NULL || *t > key) {
        // if we have reached level 0 
        // the key is not found
        if (level == 0)
            return NULL;
            
        // if the current level is not level 0, 
        // continue to search in the next level
        return find(target, key, level - 1);
    } 
    
    // Better luck next time:
    // the node we are searching 
    // may still be in the current level
	return find(t, key, level);
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTION ////////////////////////
/////////////////////////////////////////////////////////////
SkipListNode* SkipList::del(SkipListNode* target, const Key& key, unsigned int level) {
    if (target->nextAtLevel(level) != NULL && *(target->nextAtLevel(level)) < key) {
        countDelete++;
    }
    
    SkipListNode* t = target->nextAtLevel(level);
    
    // we have reached the end of the current level
    if (t == NULL) {
        if (level == 0) 
            return NULL;
        return del(target, key, level - 1);
    }

    // we found the node to be deleted
    if (*t == key) {
        // delete it from the current level
        SkipListNode* nextt = t->nextAtLevel(level);
        target->setNextAtLevel(level, nextt);
        
        // delete it from the next level
        if (level > 0) 
            return del(target, key, level - 1);
            
        return t;
    }
    
    // the node may still be in the current level
    if (*t < key) {
        return del(t, key, level);
    }
    
    // the node is not in the current level
    return NULL; 
}
