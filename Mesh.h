#ifndef _MESH_H_
#define _MESH_H_

#include "precomp.h"
#include "Point.h"
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/serialization/strong_typedef.hpp>

const int MAX_VALENCE = 100;

template <class T, class U>
class Mesh
{
private:
  BOOST_STRONG_TYPEDEF(T,TIndex);
  BOOST_STRONG_TYPEDEF(T,CIndex);
  BOOST_STRONG_TYPEDEF(T,VIndex);

  VIndex m_nv;
  TIndex m_nt;
  CIndex m_nc;

  std::vector<VIndex> m_VTable;
  std::vector<VIndex> m_OTable;
  std::vector<Point<U>> m_GTable;

public:
  void addVertex( const Point<U>& p );
  void addTriangle( VIndex v1, VIndex v2, VIndex v3 );
  
  //Corner table
  TIndex t(CIndex c) const throw() { return TIndex(c/3); }
  CIndex n(CIndex c) const throw() { return CIndex(3*t(c) + (c+1)%3); }
  CIndex p(CIndex c) const throw() { return CIndex(3*t(c) + (c+2)%3); }
  VIndex v(CIndex c) const throw() { return m_VTable[c]; }
  VIndex o(CIndex c) const throw() { return m_OTable[c]; }
  CIndex l(CIndex c) const throw() { return o(n(c)); }
  CIndex r(CIndex c) const throw() { return o(p(c)); }
  CIndex s(CIndex c) const throw() { return n(l(c)); }
  CIndex u(CIndex c) const throw() { return p(r(c)); }
  CIndex c(TIndex t) const throw() { return CIndex(t*3); }
  const Point<U>& G(CIndex c) const throw() { return m_GTable[v(c)]; }

  class Swing_iterator : public std::iterator<std::input_iterator_tag, CIndex, ptrdiff_t, const CIndex*, const CIndex&> // Info about iterator
  {
  private:
    CIndex m_corner;
    bool m_fDoneAtleastOneSwing;
    Mesh<T,U> m_mesh;
  public:
    Swing_iterator( const Mesh<T,U>& mesh, int corner, bool fDoneAtleastOneSwing = false) : m_mesh( mesh ), m_corner( corner ), 
                                                                                          m_fDoneAtleastOneSwing( fDoneAtleastOneSwing ) {}
    const CIndex& operator*() const throw() { return m_corner; }
    const CIndex* operator->() const throw() { return &m_corner; }
    
    Swing_iterator& operator++() 
    {
      m_corner = m_mesh.s( m_corner ); 
      m_fDoneAtleastOneSwing = true; 
      return *this; 
    } 
    
    Swing_iterator& operator++(int) 
    { 
      m_corner = m_mesh.s( m_corner ); 
      m_fDoneAtleastOneSwing = true; 
      return *this; 
    }

    bool operator!=( const Swing_iterator& other ) const throw() { return !equals( other ); }
    bool operator==( const Swing_iterator& other ) const throw() { return equals( other ); }

  private:
    bool equals( const Swing_iterator& other ) const throw() 
    { 
      if ( &m_mesh != &other.m_mesh )
      {
        return false;
      }
      return ( m_corner == other.corner && m_fDoneAtleastOneSwing == other.m_fDoneAtleastOneSwing );
    }
  };

  Swing_iterator beginSwingIterator(int corner) { return Swing_iterator<T>( *this, corner ); }
  Swing_iterator endSwingIterator(int corner) { return Swing_iterator<T>( *this, corner, true/*fDoneAtleastOneSwing*/ ); }

  void computeO()
  {
    std::vector<CIndex> valence( m_nv );

    for (VIndex i=VIndex(0); i < m_nv; i++) 
    {
      valence[i]=CIndex(0);
    }
    for (CIndex i=CIndex(0); i < m_nc; i++)
    {
      valence[v(i)]++;
    }

    std::vector<CIndex> firstIncidentCorner(m_nv); 
    int runningFirstIncidentCorner=0; 
    
    for (VIndex i = VIndex(0); i < m_nv; i++) 
    {
      firstIncidentCorner[i] = runningFirstIncidentCorner; 
      runningFirstIncidentCorner += valence[i];
    };  // head of list of incident corners
    
    for (VIndex i=VIndex(0); i < m_nv; i++)
    {
      valence[i]=CIndex(0);   // valences wil be reused to track how many incident corners were encountered for each vertex
    }

    std::vector<CIndex> C(m_nc); 
    for ( CIndex i = CIndex(0); i < m_nc; i++ ) C[firstIncidentCorner[v(i)] + valence[v(i)]++] = i;  // for each vertex: the list of val[v] incident corners starts at C[fic[v]]
    for ( CIndex i = CIndex(0); i < m_nc; i++ ) m_OTable[i] = -1;  // init O table to -1 meaning that a corner has no opposite (i.e. faces a border)
    
    for ( VIndex i = VIndex(0); i < m_nv; i++ )
    {
      for ( CIndex c1 = firstIncidentCorner[i]; c1 < firstIncidentCorner[i] + valence[i] - 1; c1++ )
      {
        for ( CIndex c2 = CIndex(c1 + 1); c2 < firstIncidentCorner[i] + valence[i]; c2++) 
        { 
          // for each pair (C[a],C[b[]) of its incident corners
          if ( v( n( C[c1] ) ) == v( p( C[c2] ) ) )
          {
            m_OTable[ p( C[c1] ) ]=n( C[c2] ); 
            m_OTable[ n( C[c2] ) ]=p( C[c1] );
          } 
          // if C[a] follows C[b] around v, then p(C[a]) and n(C[b]) are opposite
          if ( v( n( C[c2] ) )==v( p( C[c1] ) ) )
          {
            m_OTable[ p( C[c2] ) ]=n( C[c1] ); 
            m_OTable[ n( C[c1] ) ]=p( C[c2] );
          }
        }
      }
    }
  }

  //Diagnostic
  void checkMesh()
  {
    for (CIndex i = 0; i < m_nc; i++)
    {
      int valence = 0;
      for (Swing_iterator iter = beginSwingIterator( i ); iter != endSwingIterator( i ); iter++ )
      {
         valence++;
         if ( valence > MAX_VALENCE )
         {
           LOG( "Incorrect Mesh as valence > MAX_VALENCE", DEBUG_LEVELS::ERROR );
         }
      }
    }
  }

  //TODO msati3: Push this out to a builder class sometime later
  void loadMeshVTS( const boost::filesystem::path& path, int scale = 1 ) 
  {
    LOGPERF;
    boost::iostreams::mapped_file_source file( path );
    const char *currentPtr = file.data();
    char *end = '\0';

    VIndex numberVertices = VIndex(strtoT<T>( currentPtr, &end ));
    m_nv = numberVertices;
    m_GTable.reserve( numberVertices );
    currentPtr = end + 1;

    T currentLine = 0;
    Point<U> readPoint;
    while ( errno == 0 && (currentLine++ != numberVertices) ) 
    {
      for (int i = 0; i < 3; i++)
      {
        U readValue = strtoT<U>( currentPtr, &end );
        readPoint.set(i, scale * readValue );
        currentPtr = end + 1;
      }
      m_GTable.push_back( readPoint );
    }

    TIndex numberTriangles = TIndex(strtoT<T>( currentPtr, &end ));
    m_nt = numberTriangles;
    m_nc = 3 * numberTriangles;
    m_VTable.reserve( m_nc );
    m_OTable.reserve( m_nc );
    currentPtr = end + 1;

    currentLine = 0;
    while ( errno == 0 && (currentLine++ != numberTriangles) ) 
    {
      for (int i = 0; i < 3; i++)
      {
        VIndex readVIndex = VIndex(strtoT<T>( currentPtr, &end ));
        m_VTable.push_back( readVIndex );
        currentPtr = end + 1;
      }
    }
    computeO();
  }
};

#endif//_MESH_H_