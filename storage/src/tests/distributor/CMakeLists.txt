# Copyright 2017 Yahoo Holdings. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.
vespa_add_library(storage_testdistributor TEST
    SOURCES
    blockingoperationstartertest.cpp
    bucketdatabasetest.cpp
    bucketdbmetricupdatertest.cpp
    bucketdbupdatertest.cpp
    bucketgctimecalculatortest.cpp
    bucketstateoperationtest.cpp
    distributor_host_info_reporter_test.cpp
    distributortest.cpp
    distributortestutil.cpp
    externaloperationhandlertest.cpp
    garbagecollectiontest.cpp
    getoperationtest.cpp
    idealstatemanagertest.cpp
    joinbuckettest.cpp
    maintenanceschedulertest.cpp
    mapbucketdatabasetest.cpp
    mergelimitertest.cpp
    mergeoperationtest.cpp
    messagesenderstub.cpp
    nodeinfotest.cpp
    nodemaintenancestatstrackertest.cpp
    operation_sequencer_test.cpp
    operationtargetresolvertest.cpp
    ownership_transfer_safe_time_point_calculator_test.cpp
    pendingmessagetrackertest.cpp
    persistence_metrics_set_test.cpp
    putoperationtest.cpp
    removebucketoperationtest.cpp
    removelocationtest.cpp
    removeoperationtest.cpp
    simplebucketprioritydatabasetest.cpp
    simplemaintenancescannertest.cpp
    splitbuckettest.cpp
    statecheckerstest.cpp
    statoperationtest.cpp
    statusreporterdelegatetest.cpp
    throttlingoperationstartertest.cpp
    twophaseupdateoperationtest.cpp
    updateoperationtest.cpp
    visitoroperationtest.cpp
    DEPENDS
    storage_distributor
    storage_testcommon
    storage_testhostreporter
)
