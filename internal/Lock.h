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
    #if _BME_Lock_CountFail
      _BME_POFTWBIT(CountFail)(_BME_PTFF);
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

#undef _BME_Lock_CountFail
