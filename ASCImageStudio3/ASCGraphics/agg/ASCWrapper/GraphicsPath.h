#pragma once

#include "..\ap_AggPlusEnums.h"
#include "..\ap_AggPlusTypes.h"
#include "..\ap_StringFormat.h"

#include "..\include\agg_path_storage.h"

#pragma warning(disable : 4786)

#include "..\include\agg_rasterizer_scanline_aa.h"
#include "..\include\agg_conv_transform.h"
#include "..\include\agg_conv_stroke.h"
#include "..\include\agg_conv_contour.h"
#include "..\include\agg_conv_unclose_polygon.h"

#include "..\include\agg_bezier_arc.h"
#include "..\include\agg_conv_curve.h"

#include "Matrix.h"

#include "..\..\Objects\ASCFontManager.h"
#include "..\..\Objects\Structures.h"

class ISimpleGraphicsPath
{
public:
	virtual bool _MoveTo(double x, double y)													= 0;
	virtual bool _LineTo(double x, double y)													= 0;
	virtual bool _CurveTo(double x1, double y1, double x2, double y2, double x3, double y3)		= 0;
	virtual bool _Close()																		= 0;
};

namespace Aggplus
{

class CGraphicsPath : public ISimpleGraphicsPath
{
	friend class CClip;
	friend class CASCFontManager;
	friend class CGraphics;

public:
	CGraphicsPath()
	{
		m_bEvenOdd = false;
	}

	~CGraphicsPath()
	{
	}

	CGraphicsPath* Clone()
	{
		CGraphicsPath* pNew = new CGraphicsPath();
		pNew->m_agg_ps		= m_agg_ps;
		pNew->m_bEvenOdd	= m_bEvenOdd;
		return pNew;
	}

	inline Status Reset()
	{
		m_agg_ps.remove_all(); 
		m_bIsMoveTo = false;
		return Ok;
	}

	inline void SetRuler(bool bEvenOdd)
	{
		m_bEvenOdd = bEvenOdd;
	}

public:
	inline Status StartFigure() 
	{ 
		m_agg_ps.start_new_path(); 
		return Ok; 
	}

	inline Status CloseFigure() 
	{ 
		m_agg_ps.close_polygon(); 
		return Ok; 
	}

	inline bool Is_poly_closed()
	{
		if (!m_agg_ps.total_vertices()) 
			return true;

		double x, y;
		unsigned int nTip = m_agg_ps.last_vertex(&x, &y);
		
		if (nTip & agg::path_flags_close) 
			return true;

		return false;
	}

	inline Status MoveTo(double x, double y)
	{
		m_bIsMoveTo = true;
		m_agg_ps.move_to(x, y);
		return Ok;
	}
	inline Status LineTo(double x, double y)
	{
		m_agg_ps.line_to(x, y);
		return Ok;
	}
	inline Status CurveTo(double x1, double y1, double x2, double y2, double x3, double y3)
	{
		m_agg_ps.curve4(x1, y1, x2, y2, x3, y3);
		return Ok;
	}

	inline Status AddLine(double x1, double y1, double x2, double y2)
	{
		 if (Is_poly_closed()) 
		 {
			 m_agg_ps.move_to(x1, y1);
		 }
		 else
		 {
			 m_agg_ps.line_to(x1, y1);
		 }

		 m_agg_ps.line_to(x2, y2);
		 return Ok;
	}

	inline Status AddLines(double* pPoints, int nCount)
	{
		if (4 > nCount)
		{
			return InvalidParameter;
		}
		int nRet = 0;

		if (!m_bIsMoveTo)
		{
			MoveTo(pPoints[0], pPoints[1]);
		}

		/*if (Is_poly_closed()) 
		{
			m_agg_ps.move_to((double)pPoints[0], (double)pPoints[1]);
		}
		else
		{
			m_agg_ps.line_to((double)pPoints[0], (double)pPoints[1]);
		}*/

		int n = (nCount / 2) - 1;

		for (int i = 1; i <= n; ++i)
		{
			double* points = &pPoints[i * 2];
			m_agg_ps.line_to(points[0], points[1]);
		}
		return Ok;
	}
	inline Status AddLines(float* pPoints, int nCount)
	{
		if (4 > nCount)
		{
			return InvalidParameter;
		}
		int nRet = 0;

		if (!m_bIsMoveTo)
		{
			MoveTo(pPoints[0], pPoints[1]);
		}

		/*if (Is_poly_closed()) 
		{
			m_agg_ps.move_to((double)pPoints[0], (double)pPoints[1]);
		}
		else
		{
			m_agg_ps.line_to((double)pPoints[0], (double)pPoints[1]);
		}*/

		int n = (nCount / 2) - 1;

		for (int i = 1; i <= n; ++i)
		{
			float* points = &pPoints[i * 2];
			m_agg_ps.line_to((double)points[0], (double)points[1]);
		}
		return Ok;
	}


	// ������, ������� ������ ����� ������� � ���� ��������
	inline Status AddBezier(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
	{
		if (Is_poly_closed()) 
			m_agg_ps.move_to(x1, y1);
		else   
			m_agg_ps.line_to(x1, y1);

		m_agg_ps.curve4(x2, y2, x3, y3, x4, y4);
		return Ok;
	}
	inline Status AddBeziers(double* pPoints, int nCount)
	{
		if (8 > nCount)
			return InvalidParameter;

		if (!m_bIsMoveTo)
		{
			MoveTo(pPoints[0], pPoints[1]);
		}

		double* points = pPoints;
		
		agg::curve4 curve;
		curve.approximation_method(agg::curve_inc);
		curve.approximation_scale(25.0);
		curve.init(points[0], points[1], points[2], points[3], points[4], points[5], points[6], points[7]);

		if (Is_poly_closed()) 
		{
			m_agg_ps.concat_path(curve, 0);
		}
		else
		{
			m_agg_ps.join_path(curve, 0);
		}

		int nCountTo = (nCount - 8) / 6;
		for (int i = 0; i < nCountTo; ++i)
		{
			points = pPoints + 8 + 6 * i;
			CurveTo(points[0], points[1], points[2], points[3], points[4], points[5]);
		}

		return Ok;
	}
	inline Status AddBeziers(float* pPoints, int nCount)
	{
		if (8 > nCount)
			return InvalidParameter;

		float* points = pPoints;
		
		agg::curve4 curve;
		curve.approximation_method(agg::curve_inc);
		curve.approximation_scale(25.0);
		curve.init((double)points[0], (double)points[1], (double)points[2], (double)points[3], 
			(double)points[4], (double)points[5], (double)points[6], (double)points[7]);

		if (Is_poly_closed()) 
		{
			m_agg_ps.concat_path(curve, 0);
		}
		else
		{
			m_agg_ps.join_path(curve, 0);
		}

		int nCountTo = (nCount - 8) / 6;
		for (int i = 0; i < nCountTo; ++i)
		{
			points = pPoints + 8 + 6 * i;
			CurveTo((double)points[0], (double)points[1], (double)points[2], (double)points[3], (double)points[4], (double)points[5]);
		}

		return Ok;
	}
	inline Status AddCurve(double* pPoints, int nCount)
	{
		// ���� �� �� ����������. ����������� - ��������.
		return AddBeziers(pPoints, nCount);
	}

	inline Status AddEllipse(double x, double y, double width, double height)
	{
		agg::bezier_arc arc(x+width/2.0, y+height/2.0, width/2.0, height/2.0, 0.0, agg::pi2);
		//2.3 m_agg_ps.add_path(arc, 0, true);
		m_agg_ps.join_path(arc, 0);
		return Ok;
	}
	inline Status AddRectangle(double x, double y, double width, double height)
	{
		m_agg_ps.move_to(x, y);
		m_agg_ps.line_to(x + width, y);
		m_agg_ps.line_to(x + width, y + height);
		m_agg_ps.line_to(x, y + height);
		m_agg_ps.close_polygon();
		return Ok;
	}
	inline Status AddPolygon(double* pPoints, int nCount)
	{
		if (2 > nCount)
		{
			return InvalidParameter;
		}
		int nRet = 0;

		if (Is_poly_closed()) 
		{
			m_agg_ps.move_to(pPoints[0], pPoints[1]);
		}
		else
		{
			m_agg_ps.line_to(pPoints[0], pPoints[1]);
		}

		int n = (nCount / 2) - 1;

		for (int i = 1; i < n; ++i)
		{
			double* points = &pPoints[i * 2];
			m_agg_ps.line_to(points[0], points[1]);
		}

		m_agg_ps.close_polygon();
		return Ok;
	}
	inline Status AddPath(const CGraphicsPath& oPath)
	{
		typedef agg::conv_curve<agg::path_storage> conv_crv_type;

		agg::path_storage p_copy(m_agg_ps);
		conv_crv_type p3(p_copy);

		m_agg_ps.join_path(p3, 0);
		return Ok;
	}
	inline Status AddArc(double x, double y, double width, double height, double startAngle, double sweepAngle)
	{
		if(sweepAngle >= 360.0)
		{
			sweepAngle = 360;
		}
		
		agg::bezier_arc arc(x+width/2.00, y+height/2.00, width/2.00, height/2.00, agg::deg2rad(startAngle), agg::deg2rad(sweepAngle));
		
		//2.3 m_agg_ps.add_path(arc, 0,  !z_is_poly_closed());

		if (Is_poly_closed()) 
		{
			m_agg_ps.concat_path(arc, 0);
		}
		else
		{
			m_agg_ps.join_path(arc, 0);
		}

		return Ok;
	}

	ULONG GetPointCount() const
	{
		ULONG nPointCount=0;
		ULONG nTotal = m_agg_ps.total_vertices();
		
		double x, y;
		
		for(ULONG i = 0; i < nTotal; ++i)
		{
			ULONG nTip = m_agg_ps.vertex(i, &x, &y);
			if(nTip)
			{
				if (!(nTip & agg::path_flags_close))
				{
					++nPointCount;
				}
			}
		}
		return nPointCount;
	}

	Status GetPathPoints(PointF* points, int count) const
	{
		int nTotal = m_agg_ps.total_vertices();
		double x, y;
		int i = 0, k = 0;
		
		while (k < count && i < nTotal)
		{
			unsigned int nTip = m_agg_ps.vertex(i, &x, &y);
			if (nTip)
			{
				if(!(nTip & agg::path_flags_close))
				{
					points[k].X = float(x);
					points[k].Y = float(y);
					++k;
				}
			}
			++i;
		}

		return Ok;
	}

	Status GetLastPoint(double& x, double& y)
	{
		m_agg_ps.last_vertex(&x, &y);
		return Ok;
	}

	Status GetPathPoints(double* points, int count) const
	{
		int nTotal = m_agg_ps.total_vertices();
		double x, y;
		int i = 0, k = 0;
		
		while (k < count && i < nTotal)
		{
			unsigned int nTip = m_agg_ps.vertex(i, &x, &y);
			if (nTip)
			{
				if(!(nTip & agg::path_flags_close))
				{
					points[2 * k]		= x;
					points[2 * k + 1]   = y;
					++k;
				}
			}
			++i;
		}

		return Ok;
	}

	void GetBounds(double& left, double& top, double& width, double& height)
	{
		unsigned int nTotal = m_agg_ps.total_vertices();
		if (nTotal)
		{
			agg::rect_d bounds(1e100, 1e100, -1e100, -1e100);
			double x, y;
			for(unsigned int i = 0; i < nTotal; i++)
			{
				unsigned int nTip = m_agg_ps.vertex(i, &x, &y);
				if(agg::is_vertex(nTip))
				{
					if(x < bounds.x1) bounds.x1 = x;
					if(y < bounds.y1) bounds.y1 = y;
					if(x > bounds.x2) bounds.x2 = x;
					if(y > bounds.y2) bounds.y2 = y;
				}
			}
			
			left	= bounds.x1;
			top		= bounds.y1;
			width	= (bounds.x2 - bounds.x1);
			height	= (bounds.y2 - bounds.y1);
		}
		else 
		{
			left	= 0;
			top		= 0;
			width	= 0;
			height	= 0;
		}
	}

	Status Transform(const CMatrix* matrix)
	{
		if (NULL != matrix)
		{
			agg::path_storage p2(m_agg_ps);
			agg::conv_transform<agg::path_storage> trans(p2, matrix->m_agg_mtx);
			m_agg_ps.remove_all();
			//2.3 m_agg_ps.add_path(trans, 0, false);
			m_agg_ps.concat_path(trans, 0);
		}
		return Ok;
	}

	virtual bool _MoveTo(double x, double y)
	{
		return (Ok == MoveTo(x, y));
	}
	virtual bool _LineTo(double x, double y)
	{
		return (Ok == LineTo(x, y));
	}
	virtual bool _CurveTo(double x1, double y1, double x2, double y2, double x3, double y3)
	{
		return (Ok == CurveTo(x1, y1, x2, y2, x3, y3));
	}
	virtual bool _Close()
	{
		return (Ok == CloseFigure());
	}

	Status AddString(BSTR bstrText, IASCFontManager* pFont, double x, double y)
	{
		if (NULL == pFont)
			return InvalidParameter;
		
		pFont->LoadString(bstrText, (float)x, (float)y);

		CASCFontManager* pMan = (CASCFontManager*)pFont;
		
		return (S_OK == pMan->GetStringPath3(this)) ? Ok : InvalidParameter;
	}

	void z_Stroke(const NSStructures::CPen* Pen)
	{
		if (NULL == Pen)
			return;

		typedef agg::conv_stroke<agg::path_storage> Path_Conv_Stroke;
		Path_Conv_Stroke pg(m_agg_ps);
		pg.line_join(agg::round_join);
		pg.line_cap(agg::round_cap);
		pg.approximation_scale(25.00);
		//pg.miter_limit(0.50);

		pg.width(Pen->Size);
		//pg.auto_detect_orientation(true);

		agg::path_storage psNew;
		//2.3 psNew.add_path(pg, 0, false);
		psNew.concat_path(pg, 0);

		m_agg_ps = psNew;
	}

	void Widen(const NSStructures::CPen* Pen, const CMatrix* matrix, float flatness)
	{
		if (NULL == Pen || NULL == matrix || 0.0f == flatness)
			return;

		typedef agg::conv_curve<agg::path_storage> conv_crv_type;

		typedef agg::conv_contour<conv_crv_type> Path_Conv_Contour;

		conv_crv_type crv(m_agg_ps);
		Path_Conv_Contour pg(crv);

		pg.miter_limit(0.50);
		//pg.miter_limit_theta(0.05);
		//pg.approximation_scale(2.00);

		pg.width(Pen->Size);

		agg::line_join_e LineJoin;
		switch (Pen->LineJoin)
		{
		case LineJoinMiter       : LineJoin=agg::miter_join; break;
		case LineJoinBevel       : LineJoin=agg::bevel_join; break;
		default:
		case LineJoinRound       : LineJoin=agg::round_join; break;
		case LineJoinMiterClipped: LineJoin=agg::miter_join_revert; break;
		}
		pg.line_join(LineJoin);

		pg.auto_detect_orientation(false);

		agg::path_storage psNew;
		//2.3 psNew.add_path(pg, 0, false);
		//m_agg_ps.concat_path(pg, 0);
		m_agg_ps.concat_path(pg, 0);
		m_agg_ps = psNew;
	}
	
	agg::path_storage *z_get_agg_path_storage() { return(&m_agg_ps); }

public:
	agg::path_storage m_agg_ps;
	bool m_bEvenOdd;
	bool m_bIsMoveTo;

public:

	int EllipseArc(double fX, double fY, double fXRad, double fYRad, double fAngle1, double fAngle2, BOOL bClockDirection)
	{
		int nRet = 0;
		
		while ( fAngle1 < 0 )
			fAngle1 += 360;

		while ( fAngle1 > 360 )
			fAngle1 -= 360;

		while ( fAngle2 < 0 )
			fAngle2 += 360;

		while ( fAngle2 >= 360 )
			fAngle2 -= 360;

		if ( !bClockDirection )
		{
			if ( fAngle1 <= fAngle2 )
				nRet = EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, fAngle2, FALSE );
			else
			{
				nRet += EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, 360, FALSE );
				nRet += EllipseArc2( fX, fY, fXRad, fYRad, 0, fAngle2, FALSE );
			}
		}
		else
		{
			if ( fAngle1 >= fAngle2 )
				nRet = EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, fAngle2, TRUE );
			else
			{
				nRet += EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, 0, TRUE );
				nRet += EllipseArc2( fX, fY, fXRad, fYRad, 360, fAngle2, TRUE );
			}
		}
		return nRet;
	}

	double AngToEllPrm(double fAngle, double fXRad, double fYRad)
	{
		// ������� ��� �������� ��������� ���� � ��������������� ������� �������
		// �.�. x= a cos(t) y = b sin(t) - ��������������� ������� �������.
		// x = r cos(p), y = r sin(p) => t = atan2( sin(p) / b, cos(p) / a );
		return atan2( sin( fAngle ) / fYRad,  cos( fAngle ) / fXRad );
	}

	int EllipseArc2(double fX, double fY, double fXRad, double fYRad, double fAngle1, double fAngle2, BOOL bClockDirection)
	{
		// ��������� ���� � �������
		int nRet = 0;

		double dAngle1 = fAngle1 * 3.141592 / 180;
		double dAngle2 = fAngle2 * 3.141592 / 180;

		// ������� � ����� ��������� ��������� ��������� � �������� �����
		unsigned int nFirstPointQuard  = int(fAngle1) / 90 + 1; 
		unsigned int nSecondPointQuard = int(fAngle2) / 90 + 1;
		nSecondPointQuard = min( 4, max( 1, nSecondPointQuard ) );
		nFirstPointQuard  = min( 4, max( 1, nFirstPointQuard ) );
		// �������� ����� � ��������� ����� ����
		double fStartX = 0.0, fStartY = 0.0, fEndX = 0.0, fEndY = 0.0;

		fStartX = fX + fXRad * cos( AngToEllPrm( dAngle1, fXRad, fYRad ) );
		fStartY = fY + fYRad * sin( AngToEllPrm( dAngle1, fXRad, fYRad ) );

		LineTo(fStartX, fStartY);

		// ������ ������ �� ��������

		double fCurX = fStartX, fCurY = fStartY;
		double dStartAngle = dAngle1;
		double dEndAngle = 0;

		if ( !bClockDirection )
		{
			for( unsigned int nIndex = nFirstPointQuard; nIndex <= nSecondPointQuard; nIndex++ ) 
			{
				if ( nIndex == nSecondPointQuard )
					dEndAngle = dAngle2;
				else
					dEndAngle = (90 * (nIndex ) ) * 3.141592f / 180;
				if ( !( nIndex == nFirstPointQuard ) )
					dStartAngle = (90 * (nIndex - 1 ) ) * 3.141592f / 180;

				EllipseArc3(fX, fY, fXRad, fYRad, AngToEllPrm( dStartAngle, fXRad, fYRad ), AngToEllPrm( dEndAngle, fXRad, fYRad ), &fEndX, &fEndY, FALSE);
			}
		}
		else
		{
			for( unsigned int nIndex = nFirstPointQuard; nIndex >= nSecondPointQuard; nIndex-- ) 
			{
				if ( nIndex == nFirstPointQuard )
					dStartAngle = dAngle1;
				else
					dStartAngle = (90 * (nIndex ) ) * 3.141592f / 180;
				if ( !( nIndex == nSecondPointQuard ) )
					dEndAngle = (90 * (nIndex - 1 ) ) * 3.141592f / 180;
				else
					dEndAngle = dAngle2;

				EllipseArc3(fX, fY, fXRad, fYRad, AngToEllPrm( dStartAngle, fXRad, fYRad ), AngToEllPrm( dEndAngle, fXRad, fYRad ), &fEndX, &fEndY, FALSE);
			}
		}

		return nRet;
	}

	int EllipseArc3(double fX, double fY, double fXRad, double fYRad, double dAngle1, double dAngle2, double *pfXCur, double *pfYCur, BOOL bClockDirection = FALSE)
	{
		// ���������� ���������, �������� � ����������� �����
		double fX1  = 0.0, fX2  = 0.0, fY1  = 0.0, fY2  = 0.0;
		double fCX1 = 0.0, fCX2 = 0.0, fCY1 = 0.0, fCY2 = 0.0;

		double fAlpha = sin( dAngle2 - dAngle1 ) * ( sqrt( 4.0 + 3.0 * tan( (dAngle2 - dAngle1) / 2.0 ) * tan( (dAngle2 - dAngle1) / 2.0 ) ) - 1.0 ) / 3.0;

		double fKoef = 1;

		fX1 = fX + fXRad * cos( dAngle1 );
		fY1 = fY + fYRad * sin( dAngle1 );

		fX2 = fX + fXRad * cos( dAngle2 );
		fY2 = fY + fYRad * sin( dAngle2 );

		fCX1 = fX1 - fAlpha * fXRad * sin ( dAngle1 );
		fCY1 = fY1 + fAlpha * fYRad * cos ( dAngle1 );

		fCX2 = fX2 + fAlpha * fXRad * sin ( dAngle2 );
		fCY2 = fY2 - fAlpha * fYRad * cos ( dAngle2 );

		if ( !bClockDirection )
		{
			CurveTo(fCX1, fCY1, fCX2, fCY2, fX2, fY2);

			*pfXCur = fX2; 
			*pfYCur = fY2;
		}
		else
		{
			CurveTo(fCX2, fCY2, fCX1, fCY1, fX1, fY1);

			*pfXCur = fX1; 
			*pfYCur = fY1;
		}
		return 0;
	}

	int Ellipse(double fX, double fY, double fXRad, double fYRad)
	{
		MoveTo(fX - fXRad, fY);

		double c_fKappa = 0.552;
		CurveTo(fX - fXRad, fY + fYRad * c_fKappa, fX - fXRad * c_fKappa, fY + fYRad, fX, fY + fYRad);
		CurveTo(fX + fXRad * c_fKappa, fY + fYRad, fX + fXRad, fY + fYRad * c_fKappa, fX + fXRad, fY);
		CurveTo(fX + fXRad, fY - fYRad * c_fKappa, fX + fXRad * c_fKappa, fY - fYRad, fX, fY - fYRad);
		CurveTo(fX - fXRad * c_fKappa, fY - fYRad, fX - fXRad, fY - fYRad * c_fKappa, fX - fXRad, fY);

		return 0;
	}

	Status AddArc2(double fX, double fY, double fWidth, double fHeight, double fStartAngle, double fSweepAngle)
	{
		if (0 >= fWidth || 0 >= fHeight)
			return InvalidParameter;
		
		if ( Is_poly_closed() )
		{
			double dStartAngle = fStartAngle * agg::pi / 180;
			double fStartX = fX + fWidth / 2.0 + fWidth / 2 * cos( AngToEllPrm( dStartAngle, fWidth / 2, fHeight / 2 ) );
			double fStartY = fY + fHeight / 2.0 - fHeight / 2 * sin( AngToEllPrm ( dStartAngle, fWidth / 2, fHeight / 2 ) );

			// � ������, ����� ������ �������� ������� ������������ ������� AppendEllipse, � ������� ������� MoveTo ��� ����
			if ( fSweepAngle < 360 )
				if ( Ok != MoveTo( fStartX, fStartY ) )
					return GenericError;
		}

		BOOL bClockDirection = FALSE;
		double fEndAngle = 360 - ( fSweepAngle + fStartAngle );
		double fSrtAngle = 360 - fStartAngle;
		if( fSweepAngle > 0 )
			bClockDirection = TRUE;

		if( abs(fSweepAngle) >= 360 ) // ����� ������
		{
			return (0 == Ellipse(fX + fWidth / 2, fY + fHeight / 2, fWidth / 2, fHeight / 2)) ? Ok : GenericError;
		}
		else // ���� �������
		{
			return (0 == EllipseArc(fX + fWidth / 2, fY + fHeight / 2, fWidth / 2, fHeight / 2, fSrtAngle, fEndAngle, bClockDirection)) ? Ok : GenericError;
		}
 
		return Ok;
	}


};

class CGraphicsPathSimpleConverter : public ISimpleGraphicsPath
{
	friend class CASCFontManager;
	
private:
	IASCRenderer* m_pRenderer;

	bool m_bEvenOdd;
	bool m_bIsMoveTo;
	bool m_bIsClosed;

	agg::path_storage m_agg_ps;

public:
	CGraphicsPathSimpleConverter()
	{
		m_pRenderer = NULL;

		m_bEvenOdd	= false;
		m_bIsMoveTo	= false;
		m_bIsClosed	= false;
	}

	~CGraphicsPathSimpleConverter()
	{
		RELEASEINTERFACE(m_pRenderer);
	}

public:
	inline void SetRenderer(IASCRenderer* pRenderer)
	{
		RELEASEINTERFACE(m_pRenderer);
		m_pRenderer = pRenderer;
		ADDREFINTERFACE(m_pRenderer);
	}
	inline IASCRenderer* GetRenderer(BOOL bIsAddref = FALSE)
	{
		if (bIsAddref)
		{
			ADDREFINTERFACE(m_pRenderer);
		}

		return m_pRenderer;
	}

public:
	inline bool PathCommandMoveTo(double fX, double fY)
	{
		return _MoveTo(fX, fY);
	}
	inline bool PathCommandLineTo(double fX, double fY)
	{
		return _LineTo(fX, fY);
	}
	inline bool PathCommandLinesTo(SAFEARRAY* pPoints)
	{
		if (NULL == pPoints)
			return false;

		LONG lCount = pPoints->rgsabound[0].cElements;
		double * pData = (double*)pPoints->pvData;
		
		if (2 == lCount)
		{
			return _LineTo(pData[0], pData[1]);
		}
				
		if (4 > lCount)
		{
			return false;
		}

		int nRet = 0;

		if (!m_bIsMoveTo)
		{
			_MoveTo(pData[0], pData[1]);
		}

		int n = (lCount / 2) - 1;

		for (int i = 1; i <= n; ++i)
		{
			double* points = &pData[i * 2];
			_LineTo(points[0], points[1]);
		}
		
		return true;
	}

	inline bool PathCommandCurveTo(double fX1, double fY1, double fX2, double fY2, double fX3, double fY3)
	{
		return _CurveTo(fX1, fY1, fX2, fY2, fX3, fY3);
	}
	inline bool PathCommandCurvesTo(SAFEARRAY* pPoints)
	{
		if (NULL == pPoints)
			return S_FALSE;

		LONG lCount = pPoints->rgsabound[0].cElements;
		double * pData = (double*)pPoints->pvData;

		if (8 > lCount)
			return false;

		if (!m_bIsMoveTo)
		{
			_MoveTo(pData[0], pData[1]);

			pData += 2;
			lCount -= 2;
		}
		else 
		{
			_LineTo(pData[0], pData[1]);

			pData += 2;
			lCount -= 2;
		}

		double* points = pData;
		
		int nCountTo = (lCount) / 6;
		for (int i = 0; i < nCountTo; ++i)
		{
			points = pData + 6 * i;
			_CurveTo(points[0], points[1], points[2], points[3], points[4], points[5]);
		}

		return true;
	}
	inline bool PathCommandArcTo(double fX, double fY, double fWidth, double fHeight, double fStartAngle, double fSweepAngle)
	{
		return AddArc(fX, fY, fWidth, fHeight, -fStartAngle, -fSweepAngle);
	}
	inline bool PathCommandClose()
	{
		return _Close();
	}
	inline bool PathCommandEnd()
	{
		return _Reset();
	}

	inline bool PathCommandStart()
	{
		return _Start();
	}
	inline bool PathCommandGetCurrentPoint(double* fX, double* fY)
	{
		m_agg_ps.last_vertex(fX, fY);
		return true;
	}
	inline bool PathCommandText(BSTR bsText, IASCFontManager* pManager, double fX, double fY, double fWidth, double fHeight, double fBaseLineOffset)
	{
		return AddString(bsText, pManager, fX, fY + fBaseLineOffset);
	}
	inline bool PathCommandTextEx(BSTR bsText, BSTR bsGidText, BSTR bsSourceCodeText, IASCFontManager* pManager, double fX, double fY, double fWidth, double fHeight, double fBaseLineOffset, DWORD lFlags)
	{
		if (NULL != bsGidText)
		{
			return PathCommandText(bsGidText, pManager, fX, fY, fWidth, fHeight, fBaseLineOffset);
		}
		
		return PathCommandText(bsText, pManager, fX, fY, fWidth, fHeight, fBaseLineOffset);
	}


	inline bool PathCommandGetBounds(double& left, double& top, double& width, double &height)
	{
		unsigned int nTotal = m_agg_ps.total_vertices();
		if (nTotal)
		{
			agg::rect_d bounds(1e100, 1e100, -1e100, -1e100);
			double x, y;
			for(unsigned int i = 0; i < nTotal; i++)
			{
				unsigned int nTip = m_agg_ps.vertex(i, &x, &y);
				if(agg::is_vertex(nTip))
				{
					if(x < bounds.x1) bounds.x1 = x;
					if(y < bounds.y1) bounds.y1 = y;
					if(x > bounds.x2) bounds.x2 = x;
					if(y > bounds.y2) bounds.y2 = y;
				}
			}
			
			left	= bounds.x1;
			top		= bounds.y1;
			width	= (bounds.x2 - bounds.x1);
			height	= (bounds.y2 - bounds.y1);
		}
		else 
		{
			left	= 0;
			top		= 0;
			width	= 0;
			height	= 0;
		}
		return true;
	}
	
public:

	virtual bool _MoveTo(double x, double y)
	{
		m_bIsMoveTo = true;
		m_agg_ps.move_to(x, y);

		if (NULL != m_pRenderer)
		{
			m_pRenderer->BeginCommand(c_nSimpleGraphicType);
			m_pRenderer->PathCommandMoveTo(x, y);
			m_pRenderer->EndCommand(c_nSimpleGraphicType);
		}
		return true;
	}
	virtual bool _LineTo(double x, double y)
	{
		if (!m_bIsMoveTo)
		{
			_MoveTo(x, y);
		}		
		
		m_agg_ps.line_to(x, y);
		
		if (NULL != m_pRenderer)
		{
			m_pRenderer->BeginCommand(c_nSimpleGraphicType);
			m_pRenderer->PathCommandLineTo(x, y);
			m_pRenderer->EndCommand(c_nSimpleGraphicType);
		}

		return true;
	}
	virtual bool _CurveTo(double x1, double y1, double x2, double y2, double x3, double y3)
	{
		if (!m_bIsMoveTo)
		{
			_MoveTo(x1, y1);
		}
		
		m_agg_ps.curve4(x1, y1, x2, y2, x3, y3);

		if (NULL != m_pRenderer)
		{
			m_pRenderer->BeginCommand(c_nSimpleGraphicType);
			m_pRenderer->PathCommandCurveTo(x1, y1, x2, y2, x3, y3);
			m_pRenderer->EndCommand(c_nSimpleGraphicType);
		}

		return true;
	}
	virtual bool _Close()
	{
		m_bIsClosed = true;
		m_agg_ps.close_polygon();
		
		if (NULL != m_pRenderer)
		{
			m_pRenderer->BeginCommand(c_nSimpleGraphicType);
			m_pRenderer->PathCommandClose();
			m_pRenderer->EndCommand(c_nSimpleGraphicType);
		}
		return true;
	}
	inline bool _Reset()
	{
		m_bEvenOdd	= false;
		m_bIsMoveTo	= false;
		m_bIsClosed	= false;

		m_agg_ps.remove_all(); 

		if (NULL != m_pRenderer)
		{
			m_pRenderer->BeginCommand(c_nSimpleGraphicType);
			m_pRenderer->PathCommandEnd();
			m_pRenderer->EndCommand(c_nSimpleGraphicType);
		}

		return true;
	}
	inline bool _Start()
	{
		m_agg_ps.start_new_path(); 

		if (NULL != m_pRenderer)
		{
			m_pRenderer->BeginCommand(c_nSimpleGraphicType);
			m_pRenderer->PathCommandStart();
			m_pRenderer->EndCommand(c_nSimpleGraphicType);
		}

		return true;
	}

protected:
	bool AddString(BSTR bstrText, IASCFontManager* pFont, double x, double y)
	{
		if (NULL == pFont)
			return false;
		
		pFont->LoadString(bstrText, (float)x, (float)y);

		CASCFontManager* pMan = (CASCFontManager*)pFont;
		
		return (S_OK == pMan->GetStringPath3(this)) ? true : false;
	}

	int EllipseArc(double fX, double fY, double fXRad, double fYRad, double fAngle1, double fAngle2, BOOL bClockDirection)
	{
		int nRet = 0;
		
		while ( fAngle1 < 0 )
			fAngle1 += 360;

		while ( fAngle1 > 360 )
			fAngle1 -= 360;

		while ( fAngle2 < 0 )
			fAngle2 += 360;

		while ( fAngle2 >= 360 )
			fAngle2 -= 360;

		if ( !bClockDirection )
		{
			if ( fAngle1 <= fAngle2 )
				nRet = EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, fAngle2, FALSE );
			else
			{
				nRet += EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, 360, FALSE );
				nRet += EllipseArc2( fX, fY, fXRad, fYRad, 0, fAngle2, FALSE );
			}
		}
		else
		{
			if ( fAngle1 >= fAngle2 )
				nRet = EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, fAngle2, TRUE );
			else
			{
				nRet += EllipseArc2( fX, fY, fXRad, fYRad, fAngle1, 0, TRUE );
				nRet += EllipseArc2( fX, fY, fXRad, fYRad, 360, fAngle2, TRUE );
			}
		}
		return nRet;
	}

	double AngToEllPrm(double fAngle, double fXRad, double fYRad)
	{
		// ������� ��� �������� ��������� ���� � ��������������� ������� �������
		// �.�. x= a cos(t) y = b sin(t) - ��������������� ������� �������.
		// x = r cos(p), y = r sin(p) => t = atan2( sin(p) / b, cos(p) / a );
		return atan2( sin( fAngle ) / fYRad,  cos( fAngle ) / fXRad );
	}

	int EllipseArc2(double fX, double fY, double fXRad, double fYRad, double fAngle1, double fAngle2, BOOL bClockDirection)
	{
		// ��������� ���� � �������
		int nRet = 0;

		double dAngle1 = fAngle1 * 3.141592 / 180;
		double dAngle2 = fAngle2 * 3.141592 / 180;

		// ������� � ����� ��������� ��������� ��������� � �������� �����
		unsigned int nFirstPointQuard  = int(fAngle1) / 90 + 1; 
		unsigned int nSecondPointQuard = int(fAngle2) / 90 + 1;
		nSecondPointQuard = min( 4, max( 1, nSecondPointQuard ) );
		nFirstPointQuard  = min( 4, max( 1, nFirstPointQuard ) );
		// �������� ����� � ��������� ����� ����
		double fStartX = 0.0, fStartY = 0.0, fEndX = 0.0, fEndY = 0.0;

		fStartX = fX + fXRad * cos( AngToEllPrm( dAngle1, fXRad, fYRad ) );
		fStartY = fY + fYRad * sin( AngToEllPrm( dAngle1, fXRad, fYRad ) );

		_LineTo(fStartX, fStartY);

		// ������ ������ �� ��������

		double fCurX = fStartX, fCurY = fStartY;
		double dStartAngle = dAngle1;
		double dEndAngle = 0;

		if ( !bClockDirection )
		{
			for( unsigned int nIndex = nFirstPointQuard; nIndex <= nSecondPointQuard; nIndex++ ) 
			{
				if ( nIndex == nSecondPointQuard )
					dEndAngle = dAngle2;
				else
					dEndAngle = (90 * (nIndex ) ) * 3.141592f / 180;
				if ( !( nIndex == nFirstPointQuard ) )
					dStartAngle = (90 * (nIndex - 1 ) ) * 3.141592f / 180;

				EllipseArc3(fX, fY, fXRad, fYRad, AngToEllPrm( dStartAngle, fXRad, fYRad ), AngToEllPrm( dEndAngle, fXRad, fYRad ), &fEndX, &fEndY, FALSE);
			}
		}
		else
		{
			for( unsigned int nIndex = nFirstPointQuard; nIndex >= nSecondPointQuard; nIndex-- ) 
			{
				if ( nIndex == nFirstPointQuard )
					dStartAngle = dAngle1;
				else
					dStartAngle = (90 * (nIndex ) ) * 3.141592f / 180;
				if ( !( nIndex == nSecondPointQuard ) )
					dEndAngle = (90 * (nIndex - 1 ) ) * 3.141592f / 180;
				else
					dEndAngle = dAngle2;

				EllipseArc3(fX, fY, fXRad, fYRad, AngToEllPrm( dStartAngle, fXRad, fYRad ), AngToEllPrm( dEndAngle, fXRad, fYRad ), &fEndX, &fEndY, FALSE);
			}
		}

		return nRet;
	}

	int EllipseArc3(double fX, double fY, double fXRad, double fYRad, double dAngle1, double dAngle2, double *pfXCur, double *pfYCur, BOOL bClockDirection = FALSE)
	{
		// ���������� ���������, �������� � ����������� �����
		double fX1  = 0.0, fX2  = 0.0, fY1  = 0.0, fY2  = 0.0;
		double fCX1 = 0.0, fCX2 = 0.0, fCY1 = 0.0, fCY2 = 0.0;

		double fAlpha = sin( dAngle2 - dAngle1 ) * ( sqrt( 4.0 + 3.0 * tan( (dAngle2 - dAngle1) / 2.0 ) * tan( (dAngle2 - dAngle1) / 2.0 ) ) - 1.0 ) / 3.0;

		double fKoef = 1;

		fX1 = fX + fXRad * cos( dAngle1 );
		fY1 = fY + fYRad * sin( dAngle1 );

		fX2 = fX + fXRad * cos( dAngle2 );
		fY2 = fY + fYRad * sin( dAngle2 );

		fCX1 = fX1 - fAlpha * fXRad * sin ( dAngle1 );
		fCY1 = fY1 + fAlpha * fYRad * cos ( dAngle1 );

		fCX2 = fX2 + fAlpha * fXRad * sin ( dAngle2 );
		fCY2 = fY2 - fAlpha * fYRad * cos ( dAngle2 );

		if ( !bClockDirection )
		{
			_CurveTo(fCX1, fCY1, fCX2, fCY2, fX2, fY2);

			*pfXCur = fX2; 
			*pfYCur = fY2;
		}
		else
		{
			_CurveTo(fCX2, fCY2, fCX1, fCY1, fX1, fY1);

			*pfXCur = fX1; 
			*pfYCur = fY1;
		}
		return 0;
	}

	int Ellipse(double fX, double fY, double fXRad, double fYRad)
	{
		_MoveTo(fX - fXRad, fY);

		double c_fKappa = 0.552;
		_CurveTo(fX - fXRad, fY + fYRad * c_fKappa, fX - fXRad * c_fKappa, fY + fYRad, fX, fY + fYRad);
		_CurveTo(fX + fXRad * c_fKappa, fY + fYRad, fX + fXRad, fY + fYRad * c_fKappa, fX + fXRad, fY);
		_CurveTo(fX + fXRad, fY - fYRad * c_fKappa, fX + fXRad * c_fKappa, fY - fYRad, fX, fY - fYRad);
		_CurveTo(fX - fXRad * c_fKappa, fY - fYRad, fX - fXRad, fY - fYRad * c_fKappa, fX - fXRad, fY);

		return 0;
	}

	bool AddArc(double fX, double fY, double fWidth, double fHeight, double fStartAngle, double fSweepAngle)
	{
		if (0 >= fWidth || 0 >= fHeight)
			return false;
		
		if ( Is_poly_closed() )
		{
			double dStartAngle = fStartAngle * agg::pi / 180;
			double fStartX = fX + fWidth / 2.0 + fWidth / 2 * cos( AngToEllPrm( dStartAngle, fWidth / 2, fHeight / 2 ) );
			double fStartY = fY + fHeight / 2.0 - fHeight / 2 * sin( AngToEllPrm ( dStartAngle, fWidth / 2, fHeight / 2 ) );

			// � ������, ����� ������ �������� ������� ������������ ������� AppendEllipse, � ������� ������� MoveTo ��� ����
			if ( fSweepAngle < 360 )
				if ( false == _MoveTo( fStartX, fStartY ) )
					return false;
		}

		BOOL bClockDirection = FALSE;
		double fEndAngle = 360 - ( fSweepAngle + fStartAngle );
		double fSrtAngle = 360 - fStartAngle;
		if( fSweepAngle > 0 )
			bClockDirection = TRUE;

		if( abs(fSweepAngle) >= 360 ) // ����� ������
		{
			return (0 == Ellipse(fX + fWidth / 2, fY + fHeight / 2, fWidth / 2, fHeight / 2)) ? true : false;
		}
		else // ���� �������
		{
			return (0 == EllipseArc(fX + fWidth / 2, fY + fHeight / 2, fWidth / 2, fHeight / 2, fSrtAngle, fEndAngle, bClockDirection)) ? true : false;
		}
 
		return Ok;
	}

	inline bool Is_poly_closed()
	{
		if (!m_agg_ps.total_vertices()) 
			return true;

		double x, y;
		unsigned int nTip = m_agg_ps.last_vertex(&x, &y);
		
		if (nTip & agg::path_flags_close) 
			return true;

		return false;
	}
};

}