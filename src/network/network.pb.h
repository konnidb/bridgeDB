// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: network.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_network_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_network_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3008000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3008000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_network_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_network_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[4]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_network_2eproto;
namespace network {
class AuthResponse;
class AuthResponseDefaultTypeInternal;
extern AuthResponseDefaultTypeInternal _AuthResponse_default_instance_;
class Credentials;
class CredentialsDefaultTypeInternal;
extern CredentialsDefaultTypeInternal _Credentials_default_instance_;
class Query;
class QueryDefaultTypeInternal;
extern QueryDefaultTypeInternal _Query_default_instance_;
class QueryResponse;
class QueryResponseDefaultTypeInternal;
extern QueryResponseDefaultTypeInternal _QueryResponse_default_instance_;
}  // namespace network
PROTOBUF_NAMESPACE_OPEN
template<> ::network::AuthResponse* Arena::CreateMaybeMessage<::network::AuthResponse>(Arena*);
template<> ::network::Credentials* Arena::CreateMaybeMessage<::network::Credentials>(Arena*);
template<> ::network::Query* Arena::CreateMaybeMessage<::network::Query>(Arena*);
template<> ::network::QueryResponse* Arena::CreateMaybeMessage<::network::QueryResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace network {

// ===================================================================

class Query :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:network.Query) */ {
 public:
  Query();
  virtual ~Query();

  Query(const Query& from);
  Query(Query&& from) noexcept
    : Query() {
    *this = ::std::move(from);
  }

  inline Query& operator=(const Query& from) {
    CopyFrom(from);
    return *this;
  }
  inline Query& operator=(Query&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Query& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Query* internal_default_instance() {
    return reinterpret_cast<const Query*>(
               &_Query_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Query* other);
  friend void swap(Query& a, Query& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Query* New() const final {
    return CreateMaybeMessage<Query>(nullptr);
  }

  Query* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Query>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Query& from);
  void MergeFrom(const Query& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Query* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "network.Query";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_network_2eproto);
    return ::descriptor_table_network_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string tocken = 1;
  void clear_tocken();
  static const int kTockenFieldNumber = 1;
  const std::string& tocken() const;
  void set_tocken(const std::string& value);
  void set_tocken(std::string&& value);
  void set_tocken(const char* value);
  void set_tocken(const char* value, size_t size);
  std::string* mutable_tocken();
  std::string* release_tocken();
  void set_allocated_tocken(std::string* tocken);

  // string query = 2;
  void clear_query();
  static const int kQueryFieldNumber = 2;
  const std::string& query() const;
  void set_query(const std::string& value);
  void set_query(std::string&& value);
  void set_query(const char* value);
  void set_query(const char* value, size_t size);
  std::string* mutable_query();
  std::string* release_query();
  void set_allocated_query(std::string* query);

  // @@protoc_insertion_point(class_scope:network.Query)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr tocken_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr query_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_network_2eproto;
};
// -------------------------------------------------------------------

class QueryResponse :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:network.QueryResponse) */ {
 public:
  QueryResponse();
  virtual ~QueryResponse();

  QueryResponse(const QueryResponse& from);
  QueryResponse(QueryResponse&& from) noexcept
    : QueryResponse() {
    *this = ::std::move(from);
  }

  inline QueryResponse& operator=(const QueryResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline QueryResponse& operator=(QueryResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const QueryResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const QueryResponse* internal_default_instance() {
    return reinterpret_cast<const QueryResponse*>(
               &_QueryResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(QueryResponse* other);
  friend void swap(QueryResponse& a, QueryResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline QueryResponse* New() const final {
    return CreateMaybeMessage<QueryResponse>(nullptr);
  }

  QueryResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<QueryResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const QueryResponse& from);
  void MergeFrom(const QueryResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(QueryResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "network.QueryResponse";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_network_2eproto);
    return ::descriptor_table_network_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string response = 1;
  void clear_response();
  static const int kResponseFieldNumber = 1;
  const std::string& response() const;
  void set_response(const std::string& value);
  void set_response(std::string&& value);
  void set_response(const char* value);
  void set_response(const char* value, size_t size);
  std::string* mutable_response();
  std::string* release_response();
  void set_allocated_response(std::string* response);

  // @@protoc_insertion_point(class_scope:network.QueryResponse)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr response_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_network_2eproto;
};
// -------------------------------------------------------------------

class Credentials :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:network.Credentials) */ {
 public:
  Credentials();
  virtual ~Credentials();

  Credentials(const Credentials& from);
  Credentials(Credentials&& from) noexcept
    : Credentials() {
    *this = ::std::move(from);
  }

  inline Credentials& operator=(const Credentials& from) {
    CopyFrom(from);
    return *this;
  }
  inline Credentials& operator=(Credentials&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Credentials& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Credentials* internal_default_instance() {
    return reinterpret_cast<const Credentials*>(
               &_Credentials_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Credentials* other);
  friend void swap(Credentials& a, Credentials& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Credentials* New() const final {
    return CreateMaybeMessage<Credentials>(nullptr);
  }

  Credentials* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Credentials>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Credentials& from);
  void MergeFrom(const Credentials& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Credentials* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "network.Credentials";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_network_2eproto);
    return ::descriptor_table_network_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string user = 1;
  void clear_user();
  static const int kUserFieldNumber = 1;
  const std::string& user() const;
  void set_user(const std::string& value);
  void set_user(std::string&& value);
  void set_user(const char* value);
  void set_user(const char* value, size_t size);
  std::string* mutable_user();
  std::string* release_user();
  void set_allocated_user(std::string* user);

  // string password = 2;
  void clear_password();
  static const int kPasswordFieldNumber = 2;
  const std::string& password() const;
  void set_password(const std::string& value);
  void set_password(std::string&& value);
  void set_password(const char* value);
  void set_password(const char* value, size_t size);
  std::string* mutable_password();
  std::string* release_password();
  void set_allocated_password(std::string* password);

  // @@protoc_insertion_point(class_scope:network.Credentials)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr user_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr password_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_network_2eproto;
};
// -------------------------------------------------------------------

class AuthResponse :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:network.AuthResponse) */ {
 public:
  AuthResponse();
  virtual ~AuthResponse();

  AuthResponse(const AuthResponse& from);
  AuthResponse(AuthResponse&& from) noexcept
    : AuthResponse() {
    *this = ::std::move(from);
  }

  inline AuthResponse& operator=(const AuthResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline AuthResponse& operator=(AuthResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const AuthResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const AuthResponse* internal_default_instance() {
    return reinterpret_cast<const AuthResponse*>(
               &_AuthResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(AuthResponse* other);
  friend void swap(AuthResponse& a, AuthResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline AuthResponse* New() const final {
    return CreateMaybeMessage<AuthResponse>(nullptr);
  }

  AuthResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<AuthResponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const AuthResponse& from);
  void MergeFrom(const AuthResponse& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(AuthResponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "network.AuthResponse";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_network_2eproto);
    return ::descriptor_table_network_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string token = 1;
  void clear_token();
  static const int kTokenFieldNumber = 1;
  const std::string& token() const;
  void set_token(const std::string& value);
  void set_token(std::string&& value);
  void set_token(const char* value);
  void set_token(const char* value, size_t size);
  std::string* mutable_token();
  std::string* release_token();
  void set_allocated_token(std::string* token);

  // @@protoc_insertion_point(class_scope:network.AuthResponse)
 private:
  class HasBitSetters;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr token_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_network_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Query

// string tocken = 1;
inline void Query::clear_tocken() {
  tocken_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Query::tocken() const {
  // @@protoc_insertion_point(field_get:network.Query.tocken)
  return tocken_.GetNoArena();
}
inline void Query::set_tocken(const std::string& value) {
  
  tocken_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:network.Query.tocken)
}
inline void Query::set_tocken(std::string&& value) {
  
  tocken_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:network.Query.tocken)
}
inline void Query::set_tocken(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  tocken_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:network.Query.tocken)
}
inline void Query::set_tocken(const char* value, size_t size) {
  
  tocken_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:network.Query.tocken)
}
inline std::string* Query::mutable_tocken() {
  
  // @@protoc_insertion_point(field_mutable:network.Query.tocken)
  return tocken_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Query::release_tocken() {
  // @@protoc_insertion_point(field_release:network.Query.tocken)
  
  return tocken_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Query::set_allocated_tocken(std::string* tocken) {
  if (tocken != nullptr) {
    
  } else {
    
  }
  tocken_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), tocken);
  // @@protoc_insertion_point(field_set_allocated:network.Query.tocken)
}

// string query = 2;
inline void Query::clear_query() {
  query_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Query::query() const {
  // @@protoc_insertion_point(field_get:network.Query.query)
  return query_.GetNoArena();
}
inline void Query::set_query(const std::string& value) {
  
  query_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:network.Query.query)
}
inline void Query::set_query(std::string&& value) {
  
  query_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:network.Query.query)
}
inline void Query::set_query(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  query_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:network.Query.query)
}
inline void Query::set_query(const char* value, size_t size) {
  
  query_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:network.Query.query)
}
inline std::string* Query::mutable_query() {
  
  // @@protoc_insertion_point(field_mutable:network.Query.query)
  return query_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Query::release_query() {
  // @@protoc_insertion_point(field_release:network.Query.query)
  
  return query_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Query::set_allocated_query(std::string* query) {
  if (query != nullptr) {
    
  } else {
    
  }
  query_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), query);
  // @@protoc_insertion_point(field_set_allocated:network.Query.query)
}

// -------------------------------------------------------------------

// QueryResponse

// string response = 1;
inline void QueryResponse::clear_response() {
  response_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& QueryResponse::response() const {
  // @@protoc_insertion_point(field_get:network.QueryResponse.response)
  return response_.GetNoArena();
}
inline void QueryResponse::set_response(const std::string& value) {
  
  response_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:network.QueryResponse.response)
}
inline void QueryResponse::set_response(std::string&& value) {
  
  response_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:network.QueryResponse.response)
}
inline void QueryResponse::set_response(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  response_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:network.QueryResponse.response)
}
inline void QueryResponse::set_response(const char* value, size_t size) {
  
  response_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:network.QueryResponse.response)
}
inline std::string* QueryResponse::mutable_response() {
  
  // @@protoc_insertion_point(field_mutable:network.QueryResponse.response)
  return response_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* QueryResponse::release_response() {
  // @@protoc_insertion_point(field_release:network.QueryResponse.response)
  
  return response_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void QueryResponse::set_allocated_response(std::string* response) {
  if (response != nullptr) {
    
  } else {
    
  }
  response_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), response);
  // @@protoc_insertion_point(field_set_allocated:network.QueryResponse.response)
}

// -------------------------------------------------------------------

// Credentials

// string user = 1;
inline void Credentials::clear_user() {
  user_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Credentials::user() const {
  // @@protoc_insertion_point(field_get:network.Credentials.user)
  return user_.GetNoArena();
}
inline void Credentials::set_user(const std::string& value) {
  
  user_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:network.Credentials.user)
}
inline void Credentials::set_user(std::string&& value) {
  
  user_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:network.Credentials.user)
}
inline void Credentials::set_user(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  user_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:network.Credentials.user)
}
inline void Credentials::set_user(const char* value, size_t size) {
  
  user_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:network.Credentials.user)
}
inline std::string* Credentials::mutable_user() {
  
  // @@protoc_insertion_point(field_mutable:network.Credentials.user)
  return user_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Credentials::release_user() {
  // @@protoc_insertion_point(field_release:network.Credentials.user)
  
  return user_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Credentials::set_allocated_user(std::string* user) {
  if (user != nullptr) {
    
  } else {
    
  }
  user_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), user);
  // @@protoc_insertion_point(field_set_allocated:network.Credentials.user)
}

// string password = 2;
inline void Credentials::clear_password() {
  password_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Credentials::password() const {
  // @@protoc_insertion_point(field_get:network.Credentials.password)
  return password_.GetNoArena();
}
inline void Credentials::set_password(const std::string& value) {
  
  password_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:network.Credentials.password)
}
inline void Credentials::set_password(std::string&& value) {
  
  password_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:network.Credentials.password)
}
inline void Credentials::set_password(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  password_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:network.Credentials.password)
}
inline void Credentials::set_password(const char* value, size_t size) {
  
  password_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:network.Credentials.password)
}
inline std::string* Credentials::mutable_password() {
  
  // @@protoc_insertion_point(field_mutable:network.Credentials.password)
  return password_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Credentials::release_password() {
  // @@protoc_insertion_point(field_release:network.Credentials.password)
  
  return password_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Credentials::set_allocated_password(std::string* password) {
  if (password != nullptr) {
    
  } else {
    
  }
  password_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), password);
  // @@protoc_insertion_point(field_set_allocated:network.Credentials.password)
}

// -------------------------------------------------------------------

// AuthResponse

// string token = 1;
inline void AuthResponse::clear_token() {
  token_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& AuthResponse::token() const {
  // @@protoc_insertion_point(field_get:network.AuthResponse.token)
  return token_.GetNoArena();
}
inline void AuthResponse::set_token(const std::string& value) {
  
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:network.AuthResponse.token)
}
inline void AuthResponse::set_token(std::string&& value) {
  
  token_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:network.AuthResponse.token)
}
inline void AuthResponse::set_token(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:network.AuthResponse.token)
}
inline void AuthResponse::set_token(const char* value, size_t size) {
  
  token_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:network.AuthResponse.token)
}
inline std::string* AuthResponse::mutable_token() {
  
  // @@protoc_insertion_point(field_mutable:network.AuthResponse.token)
  return token_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* AuthResponse::release_token() {
  // @@protoc_insertion_point(field_release:network.AuthResponse.token)
  
  return token_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void AuthResponse::set_allocated_token(std::string* token) {
  if (token != nullptr) {
    
  } else {
    
  }
  token_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), token);
  // @@protoc_insertion_point(field_set_allocated:network.AuthResponse.token)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace network

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_network_2eproto
