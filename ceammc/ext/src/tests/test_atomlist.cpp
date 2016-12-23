/*****************************************************************************
 * Copyright 2016 Serge Poltavsky. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ceammc_atomlist.h"
#include <cstdarg>

using namespace ceammc;

AtomList AList(size_t n_args, ...)
{
    AtomList res;
    va_list ap;
    va_start(ap, n_args);
    for (size_t i = 2; i <= n_args + 1; i++) {
        res.append(Atom(va_arg(ap, double)));
    }
    va_end(ap);
    return res;
}

TEST_CASE("AtomList", "[ceammc::AtomList]")
{
    SECTION("construct")
    {
        AtomList l;
        REQUIRE(l.empty());
        REQUIRE(l.size() == 0);
        REQUIRE(l.min() == 0);
        REQUIRE(l.max() == 0);
        REQUIRE(l.first() == 0);
        REQUIRE(l.last() == 0);
        REQUIRE(l.relativeAt(0) == 0);
        REQUIRE(l.relativeAt(1) == 0);
        REQUIRE(l.relativeAt(-1) == 0);

        l.append(Atom(1.0));
        REQUIRE_FALSE(l.empty());
        REQUIRE(l.size() == 1);
    }

    SECTION("sort numeric")
    {
        AtomList l;
        l.append(Atom(10.0f));
        l.append(Atom(2.0f));
        l.append(Atom(-3.0f));

        FloatList r1 = l.asFloats();
        REQUIRE(r1[0] == 10.0f);
        REQUIRE(r1[1] == 2.0f);
        REQUIRE(r1[2] == -3.0f);

        l.sort();
        FloatList r2 = l.asFloats();
        REQUIRE(r2[0] == -3.0f);
        REQUIRE(r2[1] == 2.0f);
        REQUIRE(r2[2] == 10.0f);

        REQUIRE(r1 != r2);
    }

    SECTION("sort symbol")
    {
        AtomList l;
        l.append(Atom(gensym("b")));
        l.append(Atom(gensym("c")));
        l.append(Atom(gensym("a")));

        REQUIRE(l.at(0).asSymbol() == gensym("b"));
        REQUIRE(l.at(1).asSymbol() == gensym("c"));
        REQUIRE(l.at(2).asSymbol() == gensym("a"));

        l.sort();

        REQUIRE(l.at(0).asSymbol() == gensym("a"));
        REQUIRE(l.at(1).asSymbol() == gensym("b"));
        REQUIRE(l.at(2).asSymbol() == gensym("c"));

        l.sort();

        REQUIRE(l.at(0).asSymbol() == gensym("a"));
        REQUIRE(l.at(1).asSymbol() == gensym("b"));
        REQUIRE(l.at(2).asSymbol() == gensym("c"));
    }

    SECTION("sort mixed")
    {
        AtomList l;
        l.sort();
        REQUIRE(l.max() == 0);
        REQUIRE(l.min() == 0);

        l.append(Atom(gensym("a")));
        l.append(Atom(2.0));
        l.append(Atom(-3.0));
        l.append(Atom(gensym("b")));
        l.append(Atom(gensym("a")));
        REQUIRE(l.size() == 5);

        REQUIRE(l.at(0).asString() == "a");
        REQUIRE(l.at(1).asFloat() == 2.0f);
        REQUIRE(l.at(2).asFloat() == -3.0f);
        REQUIRE(l.at(3).asString() == "b");
        REQUIRE(l.at(4).asString() == "a");

        l.sort();

        REQUIRE(l.at(0).asFloat() == -3.0f);
        REQUIRE(l.at(1).asFloat() == 2.0f);
        REQUIRE(l.at(2).asString() == "a");
        REQUIRE(l.at(3).asString() == "a");
        REQUIRE(l.at(4).asString() == "b");

        REQUIRE(l.max() != 0);
        REQUIRE(l.max()->asString() == "b");
        REQUIRE(l.min() != 0);
        REQUIRE(l.min()->asFloat() == -3.0f);

        const AtomList c1 = l;
        REQUIRE(c1.max() != 0);
        REQUIRE(c1.max()->asString() == "b");
        REQUIRE(c1.min() != 0);
        REQUIRE(c1.min()->asFloat() == -3.0f);
        REQUIRE(c1.first()->asFloat() == -3.0f);
        REQUIRE(c1.last()->asString() == "b");

        REQUIRE(c1.relativeAt(0)->asFloat() == -3.0f);
        REQUIRE(c1.relativeAt(-1)->asString() == "b");
        REQUIRE(c1.relativeAt(1000) == 0);
    }

    SECTION("compare")
    {
        AtomList l1, l2;
        REQUIRE(l1 == l1);
        REQUIRE(l1 == l2);
        l2.append(Atom(1.0));
        REQUIRE(l1 != l2);
    }

    SECTION("filtered")
    {
        AtomList l1;
        l1.append(Atom(gensym("a")));
        l1.append(Atom(2.0));

        AtomList l2 = l1.filtered(0);
        REQUIRE(l1 == l2);

        l2 = l1.filtered(isFloat);
        REQUIRE(l1 != l2);
        REQUIRE(l2.size() == 1);
        REQUIRE(l2.at(0).asFloat() == 2.0f);

        l2 = l1.filtered(isSymbol);
        REQUIRE(l1 != l2);
        REQUIRE(l2.size() == 1);
        REQUIRE(l2.at(0).asString() == "a");
    }

    SECTION("clear")
    {
        AtomList l1;
        l1.clear();
        REQUIRE(l1.size() == 0);
        l1.append(Atom(8.5));
        REQUIRE(l1.size() == 1);
        l1.clear();
        REQUIRE(l1.size() == 0);
    }

    SECTION("insert")
    {
        AtomList l;
        l.insert(0, Atom(1.1f));
        REQUIRE(l.size() == 1);
        REQUIRE(l.at(0).asFloat() == 1.1f);

        l.insert(0, Atom(-1.1f));
        REQUIRE(l.size() == 2);
        REQUIRE(l.at(0).asFloat() == -1.1f);

        l.insert(2, Atom(15));
        REQUIRE(l.size() == 3);
        REQUIRE(l.at(2).asFloat() == 15.f);

        l.insert(20, Atom(15));
        REQUIRE(l.size() == 3);
    }

    SECTION("remove")
    {
        AtomList l;
        l.append(Atom(1.f));
        l.append(Atom(2.f));
        l.append(Atom(3.f));

        REQUIRE(l.size() == 3);
        REQUIRE_FALSE(l.remove(20));
        REQUIRE(l.size() == 3);
        REQUIRE(l.remove(1));
        REQUIRE(l.size() == 2);
        REQUIRE(l.at(1).asFloat() == 3.f);
    }

    SECTION("find")
    {
        AtomList l;
        REQUIRE(l.find(Atom(1.0)) == 0);
        REQUIRE(l.find(isFloat) == 0);
        REQUIRE(l.findLast(1.0) == 0);
        REQUIRE(l.findLast(isFloat) == 0);

        l.append(Atom(1.f));
        l.append(Atom(2.f));
        l.append(Atom(3.f));

        const AtomList l2 = l;

        REQUIRE(l2.find(Atom(1.f)) != 0);
        REQUIRE(l2.find(Atom(2.f)) != 0);
        REQUIRE(l2.find(Atom(3.f)) != 0);
        REQUIRE(l2.find(Atom(4.f)) == 0);

        REQUIRE(l2.findLast(Atom(1.f)) != 0);
        REQUIRE(l2.findLast(Atom(2.f)) != 0);
        REQUIRE(l2.findLast(Atom(3.f)) != 0);
        REQUIRE(l2.findLast(Atom(4.f)) == 0);

        // find by predicate
        REQUIRE(l2.find(isFloat) != 0);
        REQUIRE(l2.find(isSymbol) == 0);
    }

    SECTION("find pred")
    {
        AtomList l;
        REQUIRE(l.find(isFloat) == 0);
        REQUIRE(l.find(isSymbol) == 0);
        REQUIRE(l.findLast(isFloat) == 0);
        REQUIRE(l.findLast(isSymbol) == 0);

        l.append(Atom(1.f));
        l.append(Atom(gensym("a")));
        l.append(Atom(3.f));
        l.append(Atom(gensym("b")));

        const AtomList l2 = l;

        REQUIRE(l2.find(isFloat)->asFloat() == 1.f);
        REQUIRE(l2.findLast(isFloat)->asFloat() == 3.f);
        REQUIRE(l2.find(isSymbol)->asString() == "a");
        REQUIRE(l2.findLast(isSymbol)->asString() == "b");
    }

    SECTION("count")
    {
        AtomList l;
        REQUIRE(l.count(1.0) == 0);
        REQUIRE(l.count(isFloat) == 0);
        l.append(1.1f);
        l.append(1.4f);
        REQUIRE(l.count(1.0f) == 0);
        REQUIRE(l.count(1.1f) == 1);
        REQUIRE(l.count(isFloat) == 2);
    }

    SECTION("fill")
    {
        AtomList l;
        l.append(Atom(1.f));
        l.append(Atom(2.f));
        l.append(Atom(3.f));

        l.fill(4.f);
        REQUIRE(l.count(4.f) == 3);

        AtomList l2;
        l2.fill(1.1, 10);
        REQUIRE(l2.size() == 10);
    }

    SECTION("allOff")
    {
        AtomList l;
        REQUIRE_FALSE(l.allOff(isFloat));
        l.fill(1.f, 10);
        REQUIRE(l.allOff(isFloat));
        REQUIRE_FALSE(l.allOff(isSymbol));
    }

    SECTION("anyOff")
    {
        AtomList l;
        REQUIRE_FALSE(l.anyOff(isFloat));
        l.fill(1.f, 10);
        REQUIRE(l.anyOff(isFloat));
        REQUIRE_FALSE(l.anyOff(isSymbol));
        l.append(gensym("test"));
        REQUIRE(l.anyOff(isSymbol));
    }

    SECTION("noneOff")
    {
        AtomList l;
        REQUIRE(l.noneOff(isFloat));
        l.fill(1.f, 10);
        REQUIRE_FALSE(l.noneOff(isFloat));
        REQUIRE(l.noneOff(isSymbol));
    }

    SECTION("shuffle")
    {
        AtomList l;
        l.shuffle();
    }

    SECTION("reverse")
    {
        AtomList l;
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);

        l.reverse();
        REQUIRE(l.at(0).asFloat() == 3.f);
        REQUIRE(l.at(1).asFloat() == 2.f);
        REQUIRE(l.at(2).asFloat() == 1.f);
    }

    SECTION("removeAll")
    {
        AtomList l;
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);
        l.append(1.f);
        l.append(1.f);

        l.removeAll(1.f);
        REQUIRE(l.size() == 2);
        REQUIRE(l.find(1.f) == 0);
    }

    SECTION("removeAllPred")
    {
        AtomList l;
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);
        l.append(1.f);
        l.append(1.f);
        l.append(gensym("a"));

        l.removeAll(isFloat);
        REQUIRE(l.size() == 1);
        REQUIRE(l.at(0).asString() == "a");
    }

    SECTION("replaceAll")
    {
        AtomList l;
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);
        l.append(1.f);
        l.append(1.f);

        l.replaceAll(1.f, -1.f);
        REQUIRE(l.count(-1.f) == 3);
    }

    SECTION("replaceAllPred")
    {
        AtomList l;
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);

        l.replaceAll(isFloat, gensym("x"));
        REQUIRE(l.count(isSymbol) == 3);
        REQUIRE(l.allOff(isSymbol));
    }

    SECTION("contains")
    {
        AtomList l;
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);
        l.append(1.f);
        l.append(1.f);

        REQUIRE(l.contains(1.f));
        REQUIRE(l.contains(2.f));
        REQUIRE(l.contains(3.f));
    }

    SECTION("findPos")
    {
        AtomList l;
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);
        l.append(1.f);
        l.append(1.f);

        REQUIRE(l.findPos(3.f) == 2);
        REQUIRE(l.findPos(2.f) == 1);
        REQUIRE(l.findPos(1.f) == 0);
        REQUIRE(l.findPos(100.f) == -1);
        REQUIRE(l.findPos(gensym("a")) == -1);
    }

    SECTION("clipAt")
    {
        AtomList l;
        REQUIRE(l.clipAt(0) == 0);
        l.append(1.f);
        l.append(2.f);

        const AtomList cl(l);
        REQUIRE(cl.clipAt(0)->asFloat() == 1.f);
        REQUIRE(cl.clipAt(1)->asFloat() == 2.f);
        REQUIRE(cl.clipAt(2)->asFloat() == 2.f);
        REQUIRE(cl.clipAt(200)->asFloat() == 2.f);
    }

    SECTION("clipAt1")
    {
        AtomList l;
        REQUIRE(l.clipAt(0) == 0);
        l.append(1.f);

        const AtomList cl(l);
        REQUIRE(cl.clipAt(0)->asFloat() == 1.f);
        REQUIRE(cl.clipAt(1)->asFloat() == 1.f);
        REQUIRE(cl.clipAt(2)->asFloat() == 1.f);
    }

    SECTION("wrapAt2")
    {
        AtomList l;
        REQUIRE(l.wrapAt(0) == 0);
        l.append(1.f);
        l.append(2.f);

        const AtomList cl(l);
        REQUIRE(cl.wrapAt(0)->asFloat() == 1.f);
        REQUIRE(cl.wrapAt(1)->asFloat() == 2.f);
        REQUIRE(cl.wrapAt(2)->asFloat() == 1.f);
        REQUIRE(cl.wrapAt(3)->asFloat() == 2.f);
        REQUIRE(cl.wrapAt(4)->asFloat() == 1.f);
        REQUIRE(cl.wrapAt(200)->asFloat() == 1.f);
    }

    SECTION("wrapAt1")
    {
        AtomList l;
        REQUIRE(l.wrapAt(0) == 0);
        l.append(1.f);

        const AtomList cl(l);
        REQUIRE(cl.wrapAt(0)->asFloat() == 1.f);
        REQUIRE(cl.wrapAt(1)->asFloat() == 1.f);
        REQUIRE(cl.wrapAt(2)->asFloat() == 1.f);
        REQUIRE(cl.wrapAt(3)->asFloat() == 1.f);
        REQUIRE(cl.wrapAt(4)->asFloat() == 1.f);
    }

    SECTION("foldAt3")
    {
        AtomList l;
        REQUIRE(l.foldAt(0) == 0);
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);

        const AtomList cl(l);
        REQUIRE(cl.foldAt(0)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(1)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(2)->asFloat() == 3.f);
        REQUIRE(cl.foldAt(3)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(4)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(5)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(6)->asFloat() == 3.f);
        REQUIRE(cl.foldAt(7)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(8)->asFloat() == 1.f);
    }

    SECTION("foldAt2")
    {
        AtomList l;
        REQUIRE(l.foldAt(0) == 0);
        l.append(1.f);
        l.append(2.f);

        const AtomList cl(l);
        REQUIRE(cl.foldAt(0)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(1)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(2)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(3)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(4)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(5)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(6)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(7)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(8)->asFloat() == 1.f);
    }

    SECTION("foldAt1")
    {
        AtomList l;
        REQUIRE(l.foldAt(0) == 0);
        l.append(1.f);

        const AtomList cl(l);
        REQUIRE(cl.foldAt(0)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(1)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(2)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(3)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(4)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(5)->asFloat() == 1.f);
    }

    SECTION("foldAt4")
    {
        AtomList l;
        REQUIRE(l.foldAt(0) == 0);
        l.append(1.f);
        l.append(2.f);
        l.append(3.f);
        l.append(4.f);

        const AtomList cl(l);
        REQUIRE(cl.at(0) == 1.f);
        REQUIRE(cl.foldAt(0)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(1)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(2)->asFloat() == 3.f);
        REQUIRE(cl.foldAt(3)->asFloat() == 4.f);
        REQUIRE(cl.foldAt(4)->asFloat() == 3.f);
        REQUIRE(cl.foldAt(5)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(6)->asFloat() == 1.f);
        REQUIRE(cl.foldAt(7)->asFloat() == 2.f);
        REQUIRE(cl.foldAt(8)->asFloat() == 3.f);
    }

    SECTION("toPdData")
    {
        AtomList l;
        l.append(1.f);
        l.append(gensym("a"));
        t_atom* atoms = l.toPdData();
        REQUIRE(atoms != 0);
        REQUIRE(atom_getfloat(&atoms[0]) == 1.f);
        REQUIRE(atom_getsymbol(&atoms[1]) == gensym("a"));
    }

    SECTION("subMin")
    {
        AtomList l1;
        AtomList l2;

        REQUIRE(l1.sub(l1) == l1);
        REQUIRE(l1.sub(l2) == l1);

        l1.append(1.f);
        REQUIRE(l1.sub(l1) == AtomList::zeroes(1));
        REQUIRE(l2.sub(l1) == AtomList());
        REQUIRE(l1.sub(l2) == AtomList());

        l2.append(2.f);
        REQUIRE(l1.sub(l2) == AtomList::filled(-1.f, 1));
        REQUIRE(l2.sub(l1) == AtomList::filled(1.f, 1));
    }

    SECTION("subPadZero")
    {
        AtomList l1;
        AtomList l2;

        REQUIRE(l1.sub(l1, AtomList::PADZERO) == AtomList());
        REQUIRE(l1.sub(l2, AtomList::PADZERO) == AtomList());

        l1.append(1.f);
        REQUIRE(l1.sub(l1, AtomList::PADZERO) == AtomList::zeroes(1));
        REQUIRE(l2.sub(l1, AtomList::PADZERO) == AtomList::filled(-1.f, 1));
    }

    SECTION("subClip")
    {
        AtomList l1;
        AtomList l2;

        REQUIRE(l1.sub(l1, AtomList::CLIP) == AtomList());
        REQUIRE(l1.sub(l2, AtomList::CLIP) == AtomList());

        l1.append(1.f);
        REQUIRE(l1.sub(l1, AtomList::CLIP) == AtomList::zeroes(1));
        REQUIRE(l2.sub(l1, AtomList::CLIP) == AtomList());
        REQUIRE(l1.sub(l2, AtomList::CLIP) == AtomList());

        l2.append(2.f);
        REQUIRE(l1.sub(l2, AtomList::CLIP) == AtomList::filled(-1.f, 1));
        REQUIRE(l2.sub(l1, AtomList::CLIP) == AtomList::filled(1.f, 1));

        l1.append(2.f);
        l1.append(3.f);
        l1.append(4.f);

        REQUIRE(l1.sub(l2, AtomList::CLIP) == AList(4, -1.f, 0.f, 1.f, 2.f));
        REQUIRE(l2.sub(l1, AtomList::CLIP) == AList(4, 1.f, 0.f, -1.f, -2.f));
    }

    SECTION("subWrap")
    {
        AtomList l1;
        AtomList l2;

        REQUIRE(l1.sub(l1, AtomList::WRAP) == AtomList());
        REQUIRE(l1.sub(l2, AtomList::WRAP) == AtomList());

        l1.append(1.f);
        REQUIRE(l1.sub(l1, AtomList::WRAP) == AtomList::zeroes(1));
        REQUIRE(l2.sub(l1, AtomList::WRAP) == AtomList());
        REQUIRE(l1.sub(l2, AtomList::WRAP) == AtomList());

        l2.append(2.f);
        REQUIRE(l1.sub(l2, AtomList::WRAP) == AtomList::filled(-1.f, 1));
        REQUIRE(l2.sub(l1, AtomList::WRAP) == AtomList::filled(1.f, 1));

        l1.append(2.f);
        l1.append(3.f);
        l1.append(4.f);
        l1.append(5.f);
        l1.append(6.f);
        l1.append(7.f);
        l1.append(8.f);

        l2.append(1.f);
        l2.append(3.f);

        // [1, 2, 3, 4, 5, 6, 7, 8]
        // [2, 1, 3]
        // [2, 1, 3, 2, 1, 3, 2, 1] - wrapped version
        // [-1,1, 0, 2, 4, 3, 5, 7] - diff
        REQUIRE(l1.sub(l2, AtomList::WRAP) == AList(8, -1., 1., 0., 2., 4., 3., 5., 7.));
        REQUIRE(l2.sub(l1, AtomList::WRAP) == AList(8, 1., -1., 0., -2., -4., -3., -5., -7.));
    }

    SECTION("subFold")
    {
        AtomList l1;
        AtomList l2;

        REQUIRE(l1.sub(l1, AtomList::FOLD) == AtomList());
        REQUIRE(l1.sub(l2, AtomList::FOLD) == AtomList());

        l1.append(1.f);
        REQUIRE(l1.sub(l1, AtomList::FOLD) == AtomList::zeroes(1));
        REQUIRE(l2.sub(l1, AtomList::FOLD) == AtomList());
        REQUIRE(l1.sub(l2, AtomList::FOLD) == AtomList());

        l2.append(2.f);
        REQUIRE(l1.sub(l2, AtomList::FOLD) == AtomList::filled(-1.f, 1));
        REQUIRE(l2.sub(l1, AtomList::FOLD) == AtomList::filled(1.f, 1));

        l1.append(2.f);
        l1.append(3.f);
        l1.append(4.f);
        l1.append(5.f);
        l1.append(6.f);
        l1.append(7.f);
        l1.append(8.f);

        l2.append(1.f);
        l2.append(3.f);

        // [1, 2, 3, 4, 5, 6, 7, 8]
        // [2, 1, 3]
        // [2, 1, 3, 1, 2, 1, 3, 1] - folded version
        // [-1,1, 0, 3, 3, 5, 4, 7] - diff
        REQUIRE(l1.sub(l2, AtomList::FOLD) == AList(8, -1., 1., 0., 3., 3., 5., 4., 7.));
        REQUIRE(l2.sub(l1, AtomList::FOLD) == AList(8, 1., -1., 0., -3., -3., -5., -4., -7.));
    }

    SECTION("resizePad")
    {
        AtomList l1;
        l1.resizePad(3, 1.f);
        REQUIRE(l1.size() == 3);
        REQUIRE(l1.at(0) == 1.f);
        REQUIRE(l1.at(1) == 1.f);
        REQUIRE(l1.at(2) == 1.f);

        l1.resizePad(1, 2.f);
        REQUIRE(l1.size() == 1);
        REQUIRE(l1.at(0) == 1.f);

        l1.resizePad(0, 100.f);
        REQUIRE(l1.empty());
    }

    SECTION("property")
    {
        AtomList l;
        REQUIRE_FALSE(l.property("@test", 0));

        Atom p1;
        REQUIRE_FALSE(l.property("@test", &p1));

        l.append(1.f);
        l.append(2.f);
        l.append(gensym("a"));
        l.append(gensym("@test"));
        REQUIRE_FALSE(l.property("@test", &p1));
        l.append(3.f);
        REQUIRE(l.property("@test", &p1));
        REQUIRE(p1.asFloat() == 3.f);

        l.append(gensym("@test2"));
        REQUIRE(l.hasProperty("@test2"));
        l.append(4.f);

        Atom p2;
        REQUIRE(l.property("@test2", &p2));
        REQUIRE(p2.asFloat() == 4.f);

        p1 = p2; // reset
        REQUIRE(l.property("@test", &p1));
        REQUIRE(p1.asFloat() == 3.f);
    }
}
