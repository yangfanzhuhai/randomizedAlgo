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
void setBit(unsigned long hash, bool bitValue) {
	unsigned long pocket = hash / m_pocketSize;
	unsigned long bit = hash % m_pocketSize;
	m_tickBook[pocket] |= (bitValue<<bit);
}

int getBit(unsigned long hash) {
	unsigned long pocket = hash / m_pocketSize;
	unsigned long bit = hash % m_pocketSize;
	if ((m_tickBook[pocket]<<bit) == 0)
		return 0;
	return 1;
}

bool checkKey(unsigned long hash) {
	unsigned long pack_no = hash / (m_pocketSize * key_bit_size);
	unsigned long pocket = pack_no / m_pocketSize;
	unsigned long bits = pack_no % m_pocketSize;
	unsigned long mask = (1<<(bits+1)) - 1;
	mask <<= (bits * key_bit_size);
	
	return ( (mask & m_tickBook[pocked]) != 0);
}*/



void BloomFilter::add(const Key& key) {
    countAdd++;
    ++m_tickBook[hash1(key)];
    ++m_tickBook[hash2(key)];

}


/////////////////////////////////////////////////////////////
/////////////////////  FIND FUNCTIONS ///////////////////////
/////////////////////////////////////////////////////////////


bool BloomFilter::exist(const Key& key) {
    countFind++;


    return m_tickBook[hash1(key)] && m_tickBook[hash2(key)]; //you have to replace this line with your own.
}


/////////////////////////////////////////////////////////////
/////////////////////  DEL FUNCTIONS ////////////////////////
/////////////////////////////////////////////////////////////

void BloomFilter::del(const Key& key) {
    countDelete++;
	--m_tickBook[hash1(key)];
	--m_tickBook[hash2(key)];

}


