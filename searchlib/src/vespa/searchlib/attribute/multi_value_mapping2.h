// Copyright 2016 Yahoo Inc. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#pragma once

#include <vespa/searchlib/datastore/entryref.h>
#include <vespa/searchlib/common/rcuvector.h>
#include <vespa/searchlib/datastore/array_store.h>
#include "address_space.h"

namespace search {

class AttributeVector;

namespace attribute {

/**
 * Base class for mapping from from document id to an array of values.
 */
class MultiValueMapping2Base
{
public:
    using EntryRef = datastore::EntryRef;
    using IndexVector = RcuVectorBase<EntryRef>;

protected:
    IndexVector _indices;

    MultiValueMapping2Base(const GrowStrategy &gs, vespalib::GenerationHolder &genHolder);
    virtual ~MultiValueMapping2Base();

public:
    using IndexCopyVector = vespalib::Array<EntryRef>;

    virtual MemoryUsage getMemoryUsage() const = 0;
    virtual size_t getTotalValueCnt() const = 0;
    IndexCopyVector getIndicesCopy(uint32_t size) const;

    void addDoc(uint32_t &docId);
    void shrink(uint32_t docidLimit);
    void clearDocs(uint32_t lidLow, uint32_t lidLimit, AttributeVector &v);

    // Mockups to temporarily silence code written for old multivalue mapping
    class Histogram
    {
    private:
        using HistogramM = std::vector<size_t>;
    public:
        using const_iterator = HistogramM::const_iterator;
        Histogram() : _histogram(1) { }
        size_t & operator [] (uint32_t) { return _histogram[0]; }
        const_iterator begin() const { return _histogram.begin(); }
        const_iterator   end() const { return _histogram.end(); }
    private:
        HistogramM _histogram;
    };
    Histogram getEmptyHistogram() const { return Histogram(); }
    static size_t maxValues() { return 0; }
};

/**
 * Class for mapping from from document id to an array of values.
 */
template <typename EntryT, typename RefT = datastore::EntryRefT<17> >
class MultiValueMapping2 : public MultiValueMapping2Base
{
public:
    using MultiValueType = EntryT;
private:
    using ArrayStore = datastore::ArrayStore<EntryT, RefT>;
    using generation_t = vespalib::GenerationHandler::generation_t;
    using ConstArrayRef = vespalib::ConstArrayRef<EntryT>;

    ArrayStore _store;
public:
    MultiValueMapping2(uint32_t maxSmallArraySize,
                       const GrowStrategy &gs = GrowStrategy());
    virtual ~MultiValueMapping2();
    ConstArrayRef get(uint32_t docId) const { return _store.get(_indices[docId]); }
    ConstArrayRef getDataForIdx(EntryRef idx) const { return _store.get(idx); }
    void set(uint32_t docId, ConstArrayRef values);

    // replace is generally unsafe and should only be used when
    // compacting enum store (replacing old enum index with updated enum index)
    void replace(uint32_t docId, ConstArrayRef values);

    // Pass on hold list management to underlying store
    void transferHoldLists(generation_t generation) { _store.transferHoldLists(generation); }
    void trimHoldLists(generation_t firstUsed) { _store.trimHoldLists(firstUsed); }
    template <class Reader>
    void prepareLoadFromMultiValue(Reader &) { }

    void compactWorst();

    // Following methods are not yet properly implemented.
    AddressSpace getAddressSpaceUsage() const { return AddressSpace(0, 0); }
    MemoryUsage getMemoryUsage() const override { return MemoryUsage(); }
    virtual size_t getTotalValueCnt() const override { return 0; }

    // Mockups to temporarily silence code written for old multivalue mapping
    bool enoughCapacity(const Histogram &) { return true; }
    void performCompaction(Histogram &) { }
};

} // namespace search::attribute
} // namespace search
