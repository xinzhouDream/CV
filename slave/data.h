#ifndef DATA_H_
#define DATA_H_

#include <stdbool.h>
#include "type.h"

#define RECORDNUM 100000
//#define TABLENUM  9

#define TABLENUM  3

#define VERSIONMAX 20

#define InvalidTupleId (TupleId)(0)


/* Version is used for store a version of a record */
typedef struct {
	TransactionId tid;
	CommitId cid;
	/* to stock other information of each version. */
	TupleId value;
	bool deleted;
} Version;

/* Record is a multi-version tuple structure */
typedef struct {
	TupleId tupleid;
	int rear;
	int front;
	int lcommit;
	Version VersionList[VERSIONMAX];
} Record;

/* THash is pointer to a hash table for every table */
typedef Record * THash;

typedef int VersionId;

/* the lock in the tuple is used to verify the atomic operation of transaction */
extern pthread_rwlock_t* RecordLock[TABLENUM];

/* just use to verify the atomic operation of a short-time */
extern pthread_spinlock_t* RecordLatch[TABLENUM];

/* every table will have a separated HashTable */
extern Record* TableList[TABLENUM];

extern int BucketNum[TABLENUM];
extern int BucketSize[TABLENUM];

extern uint64_t RecordNum[TABLENUM];

extern void InitRecord(void);

extern void ProcessInsert(uint64_t * recv_buffer, int conn, int index);
extern void ProcessTrulyInsert(uint64_t * recv_buffer, int conn, int index);
extern void ProcessCommitInsert(uint64_t * recv_buffer, int conn, int index);
extern void ProcessUpdate(uint64_t * recv_buffer, int conn, int index);
extern void ProcessRead(uint64_t * recv_buffer, int conn, int index);
extern void ProcessUnrwLock(uint64_t * recv_buffer, int conn, int index);
extern void ProcessUnspinLock(uint64_t * recv_buffer, int conn, int index);
extern void ProcessReadFind(uint64_t * recv_buffer, int conn, int index);
extern void ProcessCollusionInsert(uint64_t * recv_buffer, int conn, int index);
extern void ProcessReadVersion(uint64_t * recv_buffer, int conn, int index);
extern void ProcessUpdateFind(uint64_t * recv_buffer, int conn, int index);
extern void ProcessUpdateConflict(uint64_t * recv_buffer, int conn, int index);
extern void ProcessUpdateVersion(uint64_t * recv_buffer, int conn, int index);
extern void ProcessGetSidMin(uint64_t * recv_buffer, int conn, int index);
extern void ProcessUpdateStartId(uint64_t * recv_buffer, int conn, int index);
extern void ProcessUpdateCommitId(uint64_t * recv_buffer, int conn, int index);
extern void ProcessCommitUpdate(uint64_t * recv_buffer, int conn, int index);
extern void ProcessAbortUpdate(uint64_t * recv_buffer, int conn, int index);
extern void ProcessAbortInsert(uint64_t * recv_buffer, int conn, int index);
extern void ProcessResetPair(uint64_t * recv_buffer, int conn, int index);

extern bool IsInsertDone(uint32_t table_id, uint64_t index);

extern int RecordFindHole(int table_id, TupleId r, int *flag);

extern int RecordFind(int table_id, TupleId r);

extern bool MVCCVisibleRead(Record * r, VersionId v, StartId sid_max, StartId* sid_min, CommitId* cid_min);

extern bool MVCCVisiblebak(Record * r, VersionId v);

extern bool IsMVCCDeleted(Record * r, VersionId v);

extern bool isEmptyQueue(Record * r);

extern void EnQueue(Record * r, TransactionId tid, TupleId value);

extern bool MVCCVisible(Record * r, VersionId v);

extern bool IsUpdateConflictbak(Record * r, TransactionId tid);

extern bool isFullQueue(Record * r);

extern void ServiceUpdateInterval(int conn, uint64_t* buffer);

#endif
