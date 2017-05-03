/* 
 toonW.cpp
 Generated by Cutter from:
     "/home/wanlyu20/mount/stuhome/maya/projects/RfM_ris/Args/toonW.args"
 at 9.54:12am 5.19.2016
*/
#include <RixPattern.h> 
#include <RixShadingUtils.h>
#include <RixShading.h>
//#include <RixInterfaces.h>
#include <cstring>
//#include <cstdio>
//#include <sstream>
//#include <cmath>
  
class toonW : public RixPattern {
public:
  
    toonW();
    virtual ~toonW() { }
    virtual int Init(RixContext &, char const *pluginpath);
    virtual RixSCParamInfo const *GetParamTable();
    virtual void Finalize(RixContext &) { }
    virtual int ComputeOutputParams(RixShadingContext const *ctx,
                                    RtInt *noutputs, 
                                    OutputSpec **outputs,
                                    RtConstPointer instanceData,
                                    RixSCParamInfo const *ignored);
    private:
        RixMessages *m_msg;
        RixShadeFunctions *m_shd;  // Shading functions in RixInterfaces.h
        RtInt        m_enCurve;
        RtFloat        m_cthres;
        RtFloat        m_fthres;
        RtFloat        m_specRange;
        RtColorRGB    m_specColor;
        RtColorRGB    m_baseColor;
        RtColorRGB    m_edgeColor;
        RtInt        m_enFake;
        RtVector3        m_fake;
    };
  
toonW::toonW():
    m_msg(NULL),
    m_shd(NULL),
    m_enCurve(1),
    m_cthres(2.0),
    m_fthres(0.7),
    m_specRange(1.8),
    m_specColor(1,1,1),
    m_baseColor(1,0.5,0.5),
    m_edgeColor(1,0,0),
    m_enFake(0),
    m_fake(1,1,1)
    { }
  
int toonW::Init(RixContext &ctx, char const *pluginpath) {
    m_msg = (RixMessages*)ctx.GetRixInterface(k_RixMessages);
    m_shd = (RixShadeFunctions*)ctx.GetRixInterface(k_RixShadeFunctions);
  
    // Uncomment the next three lines if a rib Option will be queried.
    //RixRenderState *rstate = (RixRenderState*)ctx.GetRixInterface(k_RixRenderState);
    //RixRenderState::Type optType;
    //RtInt optNumValues, err;
    // Example of using messaging,
    //    m_msg->Info("%f\n", a_float_value);
    return (!m_msg) ? 1 : 0;
    }
  
RixSCParamInfo const *toonW::GetParamTable() {
    static RixSCParamInfo s_ptable[] = {
        // Output
        RixSCParamInfo("resultRGB", k_RixSCColor, k_RixSCOutput),
        // Inputs
        RixSCParamInfo("enCurve", k_RixSCInteger),
        RixSCParamInfo("cthres", k_RixSCFloat),
        RixSCParamInfo("fthres", k_RixSCFloat),
        RixSCParamInfo("specRange", k_RixSCFloat),
        RixSCParamInfo("specColor", k_RixSCColor),
        RixSCParamInfo("baseColor", k_RixSCColor),
        RixSCParamInfo("edgeColor", k_RixSCColor),
        RixSCParamInfo("enFake", k_RixSCInteger),
        RixSCParamInfo("fake", k_RixSCVector),
        RixSCParamInfo() // end of table
        };
    return &s_ptable[0];
    }
  
enum paramIndex {
    k_resultRGB = 0,
    k_enCurve,
    k_cthres,
    k_fthres,
    k_specRange,
    k_specColor,
    k_baseColor,
    k_edgeColor,
    k_enFake,
    k_fake
    };
    
int toonW::ComputeOutputParams(RixShadingContext const *ctx,
                                RtInt *noutputs, 
                                OutputSpec **outputs,
                                RtConstPointer instanceData,
                                RixSCParamInfo const *ignored) {
  
    // Uncomment the next three lines if a rib Attribute will be queried. Note
    // that Rib Options should be queried in the init() method - not here!
    //RixRenderState *rstate = (RixRenderState*)ctx->GetRixInterface(k_RixRenderState);
    //RixRenderState::Type attrType;
    //RtInt attrNumValues, err;
  
    // OUTPUTS BEGIN____________________________________
    // Allocate memory for the OutputSpec data structure.
    RixShadingContext::Allocator pool(ctx);
    OutputSpec *outSpec = pool.AllocForPattern<OutputSpec>(1);
    *outputs = outSpec;
  
    // Allocate memory for each output.
    RtColorRGB    *resultRGB = pool.AllocForPattern<RtColorRGB>(ctx->numPts);
  
    // Connect the output(s) to the OutputSpec.
    *noutputs = 1;
    outSpec[0].paramId = k_resultRGB;
    outSpec[0].detail = k_RixSCVarying;
    outSpec[0].value = resultRGB;
  
    // INPUTS BEGIN____________________________________
    bool varying = true;
    bool uniform = false;
    // Declare a pointer for each input then obtain their values
    // using EvalParam().
    RtInt        const *enCurvePtr;
    RtFloat        const *cthres;
    RtFloat        const *fthres;
    RtFloat        const *specRange;
    RtColorRGB    const *specColor;
    RtColorRGB    const *baseColor;
    RtColorRGB    const *edgeColor;
    RtInt        const *enFakePtr;
    RtVector3        const *fake;
    RtFloat     const *curvature;
    RtNormal3     const  *Nn;
    RtVector3     const  *Vn;
    ctx->EvalParam(k_enCurve, -1, &enCurvePtr, &m_enCurve, uniform);
    ctx->EvalParam(k_cthres, -1, &cthres, &m_cthres, varying);
    ctx->EvalParam(k_fthres, -1, &fthres, &m_fthres, varying);
    ctx->EvalParam(k_specRange, -1, &specRange, &m_specRange, varying);
    ctx->EvalParam(k_specColor, -1, &specColor, &m_specColor, varying);
    ctx->EvalParam(k_baseColor, -1, &baseColor, &m_baseColor, varying);
    ctx->EvalParam(k_edgeColor, -1, &edgeColor, &m_edgeColor, varying);
    ctx->EvalParam(k_enFake, -1, &enFakePtr, &m_enFake, uniform);
    ctx->EvalParam(k_fake, -1, &fake, &m_fake, varying);
    ctx->GetBuiltinVar(RixShadingContext::k_curvature, &curvature);
    ctx->GetBuiltinVar(RixShadingContext::k_Nn, &Nn);
    ctx->GetBuiltinVar(RixShadingContext::k_Vn, &Vn);
  
  
    // Assign values to the output(s).
    for(int i = 0; i < ctx->numPts; i++) {
         
        float dot = Vn[i].Dot(Nn[i]);
        RtVector3 temp;
        temp = fake[i];
        Normalize(temp);
        float dotL = fake[i].Dot(Nn[i]);
        //float factor = 0;
        
        if(*enFakePtr == 1){
        
            if(dot < fthres[i]){
                resultRGB[i] = edgeColor[i];
                }
            else if(dot > fthres[i] && dotL < fthres[i] * specRange[i]){
                resultRGB[i] = baseColor[i];
                }
            else{
                resultRGB[i] = specColor[i];
                }     
            }    
        else{
            if(dot < fthres[i]){
                resultRGB[i] = edgeColor[i];
                }
            else if(dot > fthres[i] && dot < fthres[i] * specRange[i]){
                resultRGB[i] = baseColor[i];
                }
            else{
                resultRGB[i] = specColor[i];
                }     
            }
        
        if(*enCurvePtr == 1){
            if(curvature[i] > cthres[i]){
            resultRGB[i] = edgeColor[i];
            }
        }
        }
    return 0;
    }
RIX_PATTERNCREATE {
    return new toonW();
    }
RIX_PATTERNDESTROY {
    delete((toonW*)pattern);
    }