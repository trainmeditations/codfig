add_library( Codfig codfig.cpp codfig.hpp codfigmodel.hpp
    applicationid.cpp applicationid.hpp
    configvalue.cpp configvalue.hpp configvalue_t.hpp
    entrycontainer.cpp entrycontainer.hpp
    configentry.cpp configentry.hpp
    configprofile.cpp configprofile.hpp
    codfigexceptions.cpp codfigexceptions.hpp
    codfigio.hpp codfigio.cpp )
add_library( CodfigFileIO codfigfileio.hpp codfigfileio.cpp )
target_link_libraries( CodfigFileIO Codfig )
