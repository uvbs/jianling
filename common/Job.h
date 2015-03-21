/******************************************************************************
Module:  Job.h
Notices: Copyright (c) 2000 Jeffrey Richter
******************************************************************************/


#pragma once


///////////////////////////////////////////////////////////////////////////////


#include <malloc.h>  // for _alloca


///////////////////////////////////////////////////////////////////////////////


class CJob
{
public:
    CJob(HANDLE hJob = NULL);
    ~CJob();

    operator HANDLE() const {return(m_hJob);}

    // Functions to create/open a job object
    BOOL Create(PSECURITY_ATTRIBUTES psa = NULL, PCTSTR pszName = NULL);
    BOOL Open(PCTSTR pszName, DWORD dwDesiredAccess,
              BOOL fInheritHandle = FALSE);

    // Functions that manipulate a job object
    BOOL AssignProcess(HANDLE hProcess);
    BOOL Terminate(UINT uExitCode = 0);

    // Functions that set limits/restrictions on the job
    BOOL SetExtendedLimitInfo(PJOBOBJECT_EXTENDED_LIMIT_INFORMATION pjoeli,
                              BOOL fPreserveJobTime = FALSE);
    BOOL SetBasicUIRestrictions(DWORD fdwLimits);
    BOOL GrantUserHandleAccess(HANDLE hUserObj, BOOL fGrant = TRUE);
    BOOL SetSecurityLimitInfo(PJOBOBJECT_SECURITY_LIMIT_INFORMATION pjosli);

    // Functions that query job limits/restrictions
    BOOL QueryExtendedLimitInfo(PJOBOBJECT_EXTENDED_LIMIT_INFORMATION pjoeli);
    BOOL QueryBasicUIRestrictions(PDWORD pfdwRestrictions);
    BOOL QuerySecurityLimitInfo(PJOBOBJECT_SECURITY_LIMIT_INFORMATION pjosli);

    // Functions that query job status information
    BOOL QueryBasicAccountingInfo(
        PJOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION pjobai);
    BOOL QueryBasicProcessIdList(DWORD dwMaxProcesses,
                                 PDWORD pdwProcessIdList, PDWORD pdwProcessesReturned = NULL);

    // Functions that set/query job event notifications
    BOOL AssociateCompletionPort(HANDLE hIOCP, ULONG_PTR CompKey);
    BOOL QueryAssociatedCompletionPort(
        PJOBOBJECT_ASSOCIATE_COMPLETION_PORT pjoacp);

    BOOL SetEndOfJobInfo(
        DWORD fdwEndOfJobInfo = JOB_OBJECT_TERMINATE_AT_END_OF_JOB);
    BOOL QueryEndOfJobTimeInfo(PDWORD pfdwEndOfJobTimeInfo);

private:
    HANDLE m_hJob;
};


