#include "BloomFilter.hpp"
const unsigned long BloomFilter::m_pocketSize = LONG_BIT;
//const unsigned int BloomFilter::key_bit_size = 4;
/***********************************************************/
/******************* PROVIDED FUNCTIONS ********************/
/***********************************************************/

void BloomFilter::init(unsigned long length) {
    m_length = (unsigned long)((2.0*length)/log(2))+1;
    m_pockets = (unsigned long)(ceil(double(m_length)/m_pocketSize));
    m_tickBook.resize(m_pockets);
    unsigned long i;
    for (i=0; i< m_pockets; i++) {
        m_tickBook[i] = 0;
    }
}

unsigned long BloomFilter::hash1(const Key& key) {
    unsigned long hash = 5381;
    unsigned int i=0;
    for (i=0; i< key.length(); i++) {
        hash = ((hash << 5) + hash) + key.c_str()[i]; /* hash * 33 + c */
    }

    double d_hash = (double) hash;

    d_hash *= (0.5*(sqrt(5)-1));
    d_hash -= floor(d_hash);
    d_hash *= (double)m_length;

    return (unsigned long)floor(d_hash);
}

unsigned long BloomFilter::hash2(const Key& key) {
    unsigned long hash = 0;
    unsigned int i=0;
    for (i=0; i< key.length(); i++) {
        hash = key.c_str()[i] + (hash << 6) + (hash << 16) - hash;
    }
    long double d_hash = (long double) hash;

    d_hash *= (0.5*(sqrtl(5)-1));
    d_hash = d_hash/10.0 - floorl(d_hash/10.0);
    d_hash *= (double)m_length;

    return (unsigned long)floorl(d_hash);
}

int BloomFilter::testExist(const Key& key, bool verbose) {
    if (exist(key)) {
        if (verbose) {
            cout<<"Key "<< key<<" is in the set"<<endl;
        }
        return 1;
    } else {
        if (verbose) {
            cout<<"Key "<< key<<" is not in the set"<<endl;
        }
        return 0;
    }
}

void BloomFilter::dump() {
    cout<<m_pockets<<" Pockets: ";
    unsigned long i;
    for (i=0; i< m_pockets; i++) {
        cout<< m_tickBook[i]<<" ";
    }
    cout<<endl;
}

/***********************************************************/
/****************  FUNCTIONS TO BE COMPLETED  ***************/
/***********************************************************/

/////////////////////////////////////////////////////////////
/////////////////////  ADD FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////
/* Some stuff I tested.. But seemed a bit complicated, I don't think
 * he intends to make us implement this. I'll keep this here for now
 * and delete it once all gets confirmed:

}*/
/*
void bit_to_one(const unsigned long bit) {
	unsigned long pocket = bit * LONG_BIT / m_length ;
	unsigned long bit_position = bit % LONG_BIT;
	m_tickBook.length();
	m_tickBook[pocket] |= (1<<bit_position);
}

void bit_to_zero(const unsigned long bit) {
	unsigned long pocket = bit * LONG_BIT / m_length ;
	unsigned long bit_position = bit % LONG_BIT;
	m_tickBook[pocket] &= ~(1<<bit_position);
}

bool check_bit(const unsigned long bit) {
	unsigned long pocket = bit * LONG_BIT / m_length ;
	unsigned long bit_position = bit % LONG_BIT;
	return (m_tickBook[pocket] & (1<<bit_position)) != 0;
}
*/
inline unsigned long get_pocket(int bit, int m_length) {
	return bit * LONG_BIT / m_length;
}

inline unsigned long get_bit_position(int bit, int m_length) {
	return bit % LONG_BIT;
}

void BloomFilter::add(const Key& key) {
    countAdd++;
    int h1,h2;
    h1 = hash1(key);
    h2 = hash2(key);
    m_tickBook[get_pocket(h1, m_length)] |= 
    (1 << get_bit_position(h1, m_length));
    
    m_tickBook[get_pocket(h2, m_length)] |= 
    (1 << get_bit_position(h2, m_length));
   
}

/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////


bool BloomFilter::exist(const Key& key) {
    countFind++;
	int h1,h2;
    h1 = hash1(key);
    h2 = hash2(key);
    return ((m_tickBook[get_pocket(h1, m_length)] & 
			(1<< get_bit_position(h1, m_length) )) !=0) &&
			((m_tickBook[get_pocket(h2, m_length)] & 
			(1<< get_bit_position(h2, m_length) )) !=0) ;
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

void BloomFilter::del(const Key& key) {
    countDelete++;
    int h1,h2;
    h1 = hash1(key);
    h2 = hash2(key);
    m_tickBook[get_pocket(h1, m_length)] &= 
    ~(1 << get_bit_position(h1, m_length));
    
    m_tickBook[get_pocket(h2, m_length)] &= 
    ~(1 << get_bit_position(h2, m_length));

}


