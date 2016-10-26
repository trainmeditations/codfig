add_library( Codfig codfig.cpp codfig.h codfigmodel.h
    applicationid.cpp applicationid.h
    configvalue.cpp configvalue.h configvalue_t.h
    entrycontainer.cpp entrycontainer.h
    configentry.cpp configentry.h
    configprofile.cpp configprofile.h
    codfigexceptions.cpp codfigexceptions.h codfigio.h codfigio.cpp )
add_library( CodfigFileIO codfigfileio.h codfigfileio.cpp )
target_link_libraries( CodfigFileIO Codfig)
