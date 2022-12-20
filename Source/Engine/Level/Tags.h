// Copyright (c) 2012-2022 Wojciech Figat. All rights reserved.

#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Core/Collections/Array.h"

/// <summary>
/// Gameplay tag that represents a hierarchical name of the form 'X.Y.Z' (namespaces separated with a dot). Tags are defined in project LayersAndTagsSettings asset but can be also created from code.
/// </summary>
API_STRUCT(NoDefault) struct FLAXENGINE_API Tag
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(Tag);

    /// <summary>
    /// Index of the tag (in global Level.Tags list).
    /// </summary>
    API_FIELD() int32 Index = -1;

    /// <summary>
    /// Gets the tag name.
    /// </summary>
    const String& ToString() const;

public:
    Tag() = default;

    FORCE_INLINE Tag(int32 index)
        : Index(index)
    {
    }

    FORCE_INLINE operator bool() const
    {
        return Index != -1;
    }

    FORCE_INLINE bool operator==(const Tag& other) const
    {
        return Index == other.Index;
    }

    FORCE_INLINE bool operator!=(const Tag& other) const
    {
        return Index != other.Index;
    }

    bool operator==(const StringView& other) const;
    bool operator!=(const StringView& other) const;
};

template<>
struct TIsPODType<Tag>
{
    enum { Value = true };
};

inline uint32 GetHash(const Tag& key)
{
    return (uint32)key.Index;
}

/// <summary>
/// Gameplay tags utilities.
/// </summary>
API_CLASS(Static) class FLAXENGINE_API Tags
{
    DECLARE_SCRIPTING_TYPE_MINIMAL(Tags);

    /// <summary>
    /// List of all tags.
    /// </summary>
    API_FIELD(ReadOnly) static Array<String> List;

    /// <summary>
    /// Gets or adds the tag.
    /// </summary>
    /// <param name="tagName">The tag name.</param>
    /// <returns>The tag.</returns>
    API_FUNCTION() static Tag Get(const StringView& tagName);

public:
    /// <summary>
    /// Checks if the list of tags contains a given tag (including parent tags check). For example, HasTag({"A.B"}, "A") returns true, for exact check use HasTagExact.
    /// </summary>
    /// <param name="list">The tags list to use.</param>
    /// <param name="tag">The tag to check.</param>
    /// <returns>True if given tag is contained by the list of tags. Returns false for empty list.</returns>
    static bool HasTag(const Array<Tag>& list, const Tag& tag);

    /// <summary>
    /// Checks if the list of tags contains a given tag (exact match). For example, HasTag({"A.B"}, "A") returns false, for parents check use HasTag.
    /// </summary>
    /// <param name="list">The tags list to use.</param>
    /// <param name="tag">The tag to check.</param>
    /// <returns>True if given tag is contained by the list of tags. Returns false for empty list.</returns>
    static bool HasTagExact(const Array<Tag>& list, const Tag& tag);

    /// <summary>
    /// Checks if the list of tags contains any of the given tags (including parent tags check). For example, HasAny({"A.B", "C"}, {"A"}) returns true, for exact check use HasAnyExact.
    /// </summary>
    /// <param name="list">The tags list to use.</param>
    /// <param name="tags">The tags to check.</param>
    /// <returns>True if any of of the given tags is contained by the list of tags.</returns>
    static bool HasAny(const Array<Tag>& list, const Array<Tag>& tags);

    /// <summary>
    /// Checks if the list of tags contains any of the given tags (exact match). For example, HasAnyExact({"A.B", "C"}, {"A"}) returns false, for parents check use HasAny.
    /// </summary>
    /// <param name="list">The tags list to use.</param>
    /// <param name="tags">The tags to check.</param>
    /// <returns>True if any of the given tags is contained by the list of tags.</returns>
    static bool HasAnyExact(const Array<Tag>& list, const Array<Tag>& tags);

    /// <summary>
    /// Checks if the list of tags contains all of the given tags (including parent tags check). For example, HasAll({"A.B", "C"}, {"A", "C"}) returns true, for exact check use HasAllExact.
    /// </summary>
    /// <param name="list">The tags list to use.</param>
    /// <param name="tags">The tags to check.</param>
    /// <returns>True if all of the given tags are contained by the list of tags. Returns true for empty list.</returns>
    static bool HasAll(const Array<Tag>& list, const Array<Tag>& tags);

    /// <summary>
    /// Checks if the list of tags contains all of the given tags (exact match). For example, HasAllExact({"A.B", "C"}, {"A", "C"}) returns false, for parents check use HasAll.
    /// </summary>
    /// <param name="list">The tags list to use.</param>
    /// <param name="tags">The tags to check.</param>
    /// <returns>True if all of the given tags are contained by the list of tags. Returns true for empty list.</returns>
    static bool HasAllExact(const Array<Tag>& list, const Array<Tag>& tags);

private:
    API_FUNCTION(NoProxy) static const String& GetTagName(int32 tag);
};

#if !BUILD_RELEASE
extern FLAXENGINE_API String* TagsListDebug; // Used by flax.natvis
#endif
