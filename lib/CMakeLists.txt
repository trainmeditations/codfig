add_library( Codfig codfig.cpp codfig.hpp
    applicationid.cpp applicationid.hpp
    configvalue.cpp configvalue.hpp configvalue_t.hpp
    entrycontainer.cpp entrycontainer.hpp
    configentry.cpp configentry.hpp
    configprofile.cpp configprofile.hpp
    codfigexceptions.cpp codfigexceptions.hpp
    codfigio.hpp codfigio_t.hpp codfigio.cpp )
target_compile_features(Codfig PUBLIC cxx_deleted_functions cxx_auto_type)
add_library( CodfigFileIO codfigfileio.hpp codfigfileio.cpp )
target_link_libraries( CodfigFileIO Codfig )
