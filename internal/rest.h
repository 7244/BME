#if !BME_set_Pad
  #pragma pack(push, 1)
#endif
BME_StructBegin(_BME_P(t))
  #if defined(BME_set_Conditional)
    #if defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
      pthread_mutex_t mutex;
      pthread_cond_t cond;
    #elif defined(__platform_windows) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
      CRITICAL_SECTION mutex;
      CONDITION_VARIABLE cond;
    #else
      #error ?
    #endif
  #else
    #if defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
      pthread_mutex_t mutex;
    #elif !BME_set_Sleep
      uint8_t value;
      #if BME_set_CountLockFail
        uint64_t LockFailCount;
      #endif
    #else
      #error ?
    #endif
  #endif

  #if BME_set_Language == 1
    #if BME_set_Sleep
      _BME_P(t)(){
        Open();
      }
      ~_BME_P(t)(){
        Close();
      }
    #else
      _BME_P(t)(){
        Init();
      }
    #endif
  #endif
#if BME_set_Language == 0
  BME_StructEnd(_BME_P(t))
#endif

__forceinline
_BME_SOFTWBIT
bool
_BME_POFTWBIT(Peek)(
  _BME_DTFF
){
  #if !defined(BME_set_Conditional) && !BME_set_Sleep
    return __atomic_load_n(&_BME_GetType->value, __ATOMIC_SEQ_CST);
  #else
    #error ?
  #endif
}

__forceinline
_BME_SOFTWBIT
#if BME_set_LockValue == 0
  void
#else
  bool
#endif
_BME_POFTWBIT(Lock)(
  _BME_DTFF
){
  #if defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
    int r = pthread_mutex_lock(&_BME_GetType->mutex);
    if(r != 0){
      __abort();
    }
    #if BME_set_LockValue == 1
      return 0;
    #endif
  #elif defined(BME_set_Conditional) && defined(__platform_windows) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
    EnterCriticalSection(&_BME_GetType->mutex);
    #if BME_set_LockValue == 1
      return 0;
    #endif
  #elif !defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
    int r = pthread_mutex_lock(&_BME_GetType->mutex);
    if(r != 0){
      __abort();
    }
    #if BME_set_LockValue == 1
      return 0;
    #endif
  #elif !defined(BME_set_Conditional) && !BME_set_Sleep
    while(__atomic_exchange_n(&_BME_GetType->value, 1, __ATOMIC_SEQ_CST)){
      #if defined(BME_set_CountLockFailGlobal)
        __atomic_add_fetch(BME_set_CountLockFailGlobal, 1, __ATOMIC_SEQ_CST);
      #endif
      #if BME_set_CountLockFail
        __atomic_add_fetch(&_BME_GetType->LockFailCount, 1, __ATOMIC_SEQ_CST);
      #endif
      #if BME_set_LockValue == 1
        return 1;
      #else
        while(_BME_GetType->value){
          __builtin_ia32_pause();
        }
      #endif
    }
    #if BME_set_LockValue == 1
      return 0;
    #endif
  #else
    #error ?
  #endif
}

__forceinline
_BME_SOFTWBIT
void
_BME_POFTWBIT(Unlock)(
  _BME_DTFF
){
  #if defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
    int r = pthread_mutex_unlock(&_BME_GetType->mutex);
    if(r != 0){
      __abort();
    }
  #elif defined(BME_set_Conditional) && defined(__platform_windows) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
    LeaveCriticalSection(&_BME_GetType->mutex);
  #elif !defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
    int r = pthread_mutex_unlock(&_BME_GetType->mutex);
    if(r != 0){
      __abort();
    }
  #elif !defined(BME_set_Conditional) && !BME_set_Sleep
    __atomic_exchange_n(&_BME_GetType->value, 0, __ATOMIC_SEQ_CST);
  #else
    #error ?
  #endif
}

#ifdef BME_set_Conditional
  __forceinline
  _BME_SOFTWBIT
  void
  _BME_POFTWBIT(Wait)(
    _BME_DTFF
  ){
    #if defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
      int r = pthread_cond_wait(&_BME_GetType->cond, &_BME_GetType->mutex);
      if(r != 0){
        __abort();
      }
    #elif defined(BME_set_Conditional) && defined(__platform_windows) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
      bool r = SleepConditionVariableCS(&_BME_GetType->cond, &_BME_GetType->mutex, INFINITE);
      if(r == 0){
        __abort();
      }
    #else
      #error ?
    #endif
  }

  __forceinline
  _BME_SOFTWBIT
  void
  _BME_POFTWBIT(Signal)(
    _BME_DTFF
  ){
    #if defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
      int r = pthread_cond_signal(&_BME_GetType->cond);
      if(r != 0){
        __abort();
      }
    #elif defined(BME_set_Conditional) && defined(__platform_windows) && defined(__platform_libc) && !BME_set_NoLibrary && BME_set_Sleep
      WakeConditionVariable(&_BME_GetType->cond);
    #else
      #error ?
    #endif
  }
#endif

#if BME_set_Language != 0
  private:
#endif
#if BME_set_Sleep
  _BME_SOFTWBIT
  void
  _BME_POFTWBIT(Open)(
    _BME_DTFF
  ){
    #if defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary
      int r = pthread_mutex_init(&_BME_GetType->mutex, NULL);
      if(r != 0){
        __abort();
      }
      r = pthread_cond_init(&_BME_GetType->cond, NULL);
      if(r != 0){
        __abort();
      }
    #elif defined(BME_set_Conditional) && defined(__platform_windows) && defined(__platform_libc) && !BME_set_NoLibrary
      InitializeCriticalSection(&_BME_GetType->mutex);
      InitializeConditionVariable(&_BME_GetType->cond);
    #elif !defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary
      int r = pthread_mutex_init(&_BME_GetType->mutex, NULL);
      if(r != 0){
        __abort();
      }
    #else
      #error ?
    #endif

    #if BME_set_CountLockFail
      _BME_GetType->LockFailCount = 0;
    #endif
  }

  _BME_SOFTWBIT
  void
  _BME_POFTWBIT(Close)(
    _BME_DTFF
  ){
    #if defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary
      int r = pthread_mutex_destroy(&_BME_GetType->mutex);
      if(r != 0){
        __abort();
      }
      r = pthread_cond_destroy(&_BME_GetType->cond);
      if(r != 0){
        __abort();
      }
    #elif defined(BME_set_Conditional) && defined(__platform_windows) && defined(__platform_libc) && !BME_set_NoLibrary
      DeleteCriticalSection(&_BME_GetType->mutex);
    #elif !defined(BME_set_Conditional) && defined(__platform_unix) && defined(__platform_libc) && !BME_set_NoLibrary
      int r = pthread_mutex_destroy(&_BME_GetType->mutex);
      if(r != 0){
        __abort();
      }
    #else
      #error ?
    #endif
  }
#else /* #if BME_set_Sleep */
  _BME_SOFTWBIT
  void
  _BME_POFTWBIT(Init)(
    _BME_DTFF
  ){
    #if !defined(BME_set_Conditional)
      _BME_GetType->value = 0;
    #else
      #error ?
    #endif

    #if BME_set_CountLockFail
      _BME_GetType->LockFailCount = 0;
    #endif
  }
#endif
#if BME_set_Language != 0
  public:
#endif

#if BME_set_Language != 0
  BME_StructEnd(_BME_P(t))
#endif
#if !BME_set_Pad
  #pragma pack(pop)
#endif
