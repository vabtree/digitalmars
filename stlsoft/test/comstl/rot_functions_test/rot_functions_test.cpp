/* /////////////////////////////////////////////////////////////////////////////
 * File:        rot_functions_test.cpp
 *
 * Purpose:     Implementation file for the rot_functions_test project.
 *
 * Created:     17th February 2003
 * Updated:     30th May 2004
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software.
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage.
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission.
 *
 * ////////////////////////////////////////////////////////////////////////// */


// This will cause various compile-time messages to be emitted. When you get
// sick of them just comment out or remove this #define
#define	_STLSOFT_COMPILE_VERBOSE

#include <stlsoft.h>

#include <comstl.h>
#include <comstl_initialisers.h>

comstl_ns_using(com_initialiser)

#include <comstl_rot_functions.h>

comstl_ns_using(Rot_Register)
comstl_ns_using(Rot_Revoke)
comstl_ns_using(Rot_IsRunning)
comstl_ns_using(Rot_GetObject)
comstl_ns_using(Rot_NoteChangeTime)
comstl_ns_using(Rot_GetTimeOfLastChange)
comstl_ns_using(Rot_EnumRunning)

#include <stdio.h>

/* ////////////////////////////////////////////////////////////////////////// */

class Unknown
	: public IUnknown
{
	STDMETHOD_(ULONG, AddRef)()
	{
		fprintf(stdout, "%p, AddRef()\n", this);

		return 0;
	}
	STDMETHOD_(ULONG, Release)()
	{
		fprintf(stdout, "%p, Release()\n", this);

		return 0;
	}
	STDMETHOD(QueryInterface)(REFIID , void **)
	{
		fprintf(stdout, "%p, QueryInterface()\n", this);

		return E_NOINTERFACE;
	}
};

/* ////////////////////////////////////////////////////////////////////////// */


int main(int /* argc */, char ** /*argv*/)
{
#if 0
	Unknown		unknown;
	DWORD		dwRegister;
	HRESULT		hr	=	Rot_Register(0, &unknown,
                            LPUNKNOWN   punkObject,
                            LPMONIKER   pmkObjectName,
                            DWORD       *pdwRegister)
#endif /* 0 */

	com_initialiser	coinit;

	IMoniker	*pmk;
	IBindCtx	*pbc;
	ULONG		cchEaten;
	HRESULT		hr;

	hr	=	::CreateBindCtx(0, &pbc);

	if(SUCCEEDED(hr))
	{
		hr	=	::MkParseDisplayName(pbc, L"H:\\Contract.doc", &cchEaten, &pmk);

		if(SUCCEEDED(hr))
		{
			LPUNKNOWN	punk;

			if(SUCCEEDED(pmk->BindToObject(pbc, NULL, IID_IUnknown, (void**)&punk)))
			{
				punk->Release();
			}

			pmk->Release();
		}

		IEnumMoniker	*penMkr;

		hr	=	Rot_EnumRunning(&penMkr);

		if(SUCCEEDED(hr))
		{
			IMoniker	*mkr;

			for(penMkr->Reset(); S_OK == penMkr->Next(1, &mkr, NULL); )
			{
				LPOLESTR	poszName;

				if(SUCCEEDED(mkr->GetDisplayName(pbc, NULL, &poszName)))
				{
					OutputDebugStringW(poszName);
					OutputDebugStringW(L"\n");

					::CoTaskMemFree(poszName);
				}
			}

			penMkr->Release();
		}

		pbc->Release();
	}

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
