#pragma once
#include <stdio.h>
#include <cstdint>
#include <string.h>
#include "../homerus.hpp"
#include "adaptor.hpp"
namespace folklore{ namespace homerus
{
	namespace ana
	{
		template <uint8_t Off,uint8_t Siz,bool Flag=(Off+Siz<=32)>
		struct bit_cut_32;
		template <uint8_t Off,uint8_t Siz>
		struct bit_cut_32<Off,Siz,true>
		{
			static uint32_t get(uint32_t val)
			{
				return (val<<(32-Off-Siz))>>(32-Siz);
			}
		};
		template <uint8_t Off,uint8_t Siz>
		struct bit_cut_32<Off,Siz,false>
		{
			static uint32_t get(uint32_t val)
			{
				return val;
			}
		};
		namespace caen
		{
			struct caen_tag{};
			namespace impl_
			{
				struct v1724_board_tag{};
				struct v1720_board_tag{};
				template <uint32_t BID,typename Btype>
				struct caen_v17xx_base:caen_tag
				{
				};
			}
#define CREATE_BITCUT_FUNC(name,offset,size,pos)                               \
	static uint32_t name(uint32_t* buf)                                        \
	{                                                                          \
		return folklore::homerus::ana::bit_cut_32<offset,size>::get(buf[pos]); \
	}
			struct block_header
			{
					CREATE_BITCUT_FUNC(flag         ,28,4 ,0);
					CREATE_BITCUT_FUNC(size         ,0 ,28,0);
					CREATE_BITCUT_FUNC(bid          ,27,5 ,1);
					CREATE_BITCUT_FUNC(channelmask  ,0 ,8 ,1);
					CREATE_BITCUT_FUNC(pattern      ,8 ,15,1);
					CREATE_BITCUT_FUNC(counter      ,0 ,23,2);
					CREATE_BITCUT_FUNC(timetag      ,0 ,32,3);
			};
			struct event_header_724
			{
				typedef impl_::v1724_board_tag board_tag;
					CREATE_BITCUT_FUNC(flag         ,28,4 ,0);
					CREATE_BITCUT_FUNC(size         ,0 ,28,0);
					CREATE_BITCUT_FUNC(nsamples     ,0 ,16,1);
					CREATE_BITCUT_FUNC(dp           ,16,4 ,1);
					CREATE_BITCUT_FUNC(vp2          ,20,2 ,1);
					CREATE_BITCUT_FUNC(vp1          ,22,2 ,1);
					CREATE_BITCUT_FUNC(is_timetag   ,28,1 ,1);
					CREATE_BITCUT_FUNC(is_energy    ,29,1 ,1);
					CREATE_BITCUT_FUNC(is_waveform  ,30,1 ,1);
					CREATE_BITCUT_FUNC(is_dualtrace ,31,1 ,1);
			};
			struct event_header_720
			{
				typedef impl_::v1720_board_tag board_tag;
					CREATE_BITCUT_FUNC(flag         ,28,4 ,0);
					CREATE_BITCUT_FUNC(size         ,0 ,28,0);
					CREATE_BITCUT_FUNC(nsamples     ,0 ,16,1);
					CREATE_BITCUT_FUNC(dp3          ,16,3 ,1);
					CREATE_BITCUT_FUNC(dp4          ,19,3 ,1);
					CREATE_BITCUT_FUNC(ap           ,22,2 ,1);
					CREATE_BITCUT_FUNC(trg_mode     ,24,2 ,1);
					CREATE_BITCUT_FUNC(is_waveform  ,27,1 ,1);
					CREATE_BITCUT_FUNC(is_baseline  ,28,1 ,1);
					CREATE_BITCUT_FUNC(is_timetag   ,29,1 ,1);
					CREATE_BITCUT_FUNC(is_energy    ,30,1 ,1);
					CREATE_BITCUT_FUNC(is_dualtrace ,31,1 ,1);
			};
#undef CREATE_BITCUT_FUNC
			template <uint32_t BID>
			struct v1724
				:folklore::homerus::ana::caen::impl_::caen_v17xx_base
				 <
				 	BID,
					folklore::homerus::ana::caen::impl_::v1724_board_tag
				>
			{
				typedef folklore::homerus::ana::caen::block_header     block_header;
				typedef folklore::homerus::ana::caen::event_header_724 event_header;
			};
			template <uint32_t BID>
			struct v1720
				:folklore::homerus::ana::caen::impl_::caen_v17xx_base
				 <
				 	BID,
					folklore::homerus::ana::caen::impl_::v1720_board_tag
				>
			{
				typedef folklore::homerus::ana::caen::block_header     block_header;
				typedef folklore::homerus::ana::caen::event_header_720 event_header;
			};
		}
		constexpr uint8_t verbose_level_silent=0;
		constexpr uint8_t verbose_level_alert =1;
		constexpr uint8_t verbose_level_normal=2;
		typedef bool *event_manager_type(void);
		class annri;
		struct energy    ;
		struct time      ;
		struct channel   ;
		struct counter   ;
		struct board     ;
		struct pur       ;
		struct ttr       ;
		struct daq_id    ;
		struct readsize  ;
		struct timestamp ;
		struct extra_bits;
		struct unique_ch ;
		struct readnext  ;
		struct board_time;
		template <typename AN_>
		class lazy_eval_t
		{
		private:
			typedef AN_ annri_type;
			annri_type* annri;
		public:
			friend energy    ;
			friend time      ;
			friend channel   ;
			friend counter   ;
			friend board     ;
			friend pur       ;
			friend ttr       ;
			friend daq_id    ;
			friend readsize  ;
			friend timestamp ;
			friend extra_bits;
			friend unique_ch ;
			friend readnext  ;
			friend board_time;
			friend class annri;
			lazy_eval_t(annri_type* a)
				:annri(a)
			{}
			lazy_eval_t()
			{}
		};
#define THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(name,typ,evname) \
		struct name                            \
		{                                      \
			typedef typ result_t;              \
			template <typename A>              \
			static inline result_t eval(A& a)  \
			{                                  \
				return (a.annri)->evname();    \
			}                                  \
		};
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(energy    ,uint32_t,eval_e      );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(time      ,uint32_t,eval_t      );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(channel   ,uint32_t,eval_ch     );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(counter   ,uint32_t,eval_counter);
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(board     ,uint32_t,eval_brd    );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(pur       ,bool    ,eval_pur    );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(ttr       ,bool    ,eval_ttr    );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(daq_id    ,uint32_t,eval_daq    );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(readsize  ,size_t  ,eval_frs    );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(timestamp ,uint64_t,eval_time   );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(extra_bits,uint8_t ,eval_extras );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(unique_ch ,uint32_t,eval_uch    );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(readnext  ,uint32_t,eval_rn     );
		THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING(board_time,uint32_t,eval_bt     );
#undef THIS_ERROR_MESSAGE_MAY_CAUSE_FROM_USING_DECLARATION_MISSING
		class wavefrom final
		{
		// not yet implemented
		};
		class annri final
		{
		private:
			FILE*           fp{nullptr};
			mutable uint8_t    verbose_level{2};
			mutable uint32_t* localbuf{nullptr};
			mutable uint32_t              rn{0};
			mutable uint32_t         evt_siz{0};
			mutable uint32_t         dat_siz{0};
			mutable uint32_t             brd{0};
			mutable uint32_t              ev{0};
			mutable uint32_t              tv{0};
			mutable uint32_t              ch{0};
			mutable uint32_t             cnt{0};
			mutable uint32_t              bt{0};
			mutable uint64_t        daq_time{0};
			mutable size_t               frs{0};
			mutable uint32_t header[4]{0,0,0,0};
			mutable bool            ttrf{false};
			mutable bool            purf{false};
			mutable bool           is_eob{true};
			mutable bool          is_eod{false};
			mutable bool         is_eval{false};
			mutable bool     is_daq_eval{false};
			mutable bool        is_start{false};
			inline void daq_header_eval(void)
			{
				memcpy(&daq_time,header+2,sizeof(daq_time));
				daq_time&=0x03ffffffffffffffUL;
				is_daq_eval=true;
			}
			inline uint32_t eval_uch(void)
			{
				return brd*8+ch;
			}
			inline uint32_t eval_bt(void)
			{
				return bt;
			}
			inline uint32_t eval_brd(void)
			{
				return brd;
			}
			inline uint32_t eval_ch(void)
			{
				return ch;
			}
			inline uint32_t eval_frs(void)
			{
				return frs;
			}
			inline uint32_t eval_rn(void)
			{
				return rn;
			}
			inline uint32_t eval_counter(void)
			{
				return cnt;
			}
			inline uint8_t eval_extras(void)
			{
				return (reinterpret_cast<uint8_t*>(localbuf+rn-1))[2];
			}
			inline uint32_t eval_daq(void)
			{
				return header[1];
			}
			inline uint64_t eval_time(void)
			{
				if(!is_daq_eval) daq_header_eval();
				return daq_time;
			}
			inline bool eval_pur(void)
			{
				if(!is_eval) eval_e();
				return purf;
			}
			inline bool eval_ttr(void)
			{
				if(!is_eval) eval_e();
				return ttrf;
			}
			inline double eval_e(void)
			{
				is_eval=true;
				purf=((localbuf[rn-1]>>15)&0x1);
				ttrf=((localbuf[rn-1]>>18)&0x1);
				ev=localbuf[rn-1]&0x3fff;
				return (double)ev;
				//ev=localbuf[rn-1];
				//return (double)ev;
			}
			inline double eval_t(void)
			{
				tv=localbuf[rn-2];
				return (double)tv;
			}
			void remove_cr(char* ar,size_t max)
			{
				for(size_t i=0;i<max;++i)
				{
					if(ar[i]=='\0') break;
					if(ar[i]=='\n')
					{
						ar[i]='\0';
						break;
					}
				}
			}
			bool get_next_block()
			{
				uint32_t hflag(0x6+is_eob);
				int32_t lch=ch;
				if(dat_siz==0||is_eod)
				{
					auto ret=fread(header,sizeof(int),4,fp);
					frs+=sizeof(int)*4;
					if(ret==EOF||ret!=4) return false;
					hflag=header[0]>>28;
					ch  =  0;
				}
				switch(hflag)
				{
					case 0x5:
						is_daq_eval=false;
						dat_siz=header[0]&0x0fffffff;
						dat_siz-=sizeof(header);
						free(localbuf);
						localbuf=(uint32_t*)malloc(dat_siz);
						if(!localbuf)
						{
							printf("malloc fail\n");
							return false;
						}
						if(fread(localbuf,dat_siz,1,fp)!=1)
						{
							printf("readsize fail\n");
							return false;
						}
						if(dat_siz>12311900)
						{
							printf("$$$ %d\n",dat_siz);
							for(int i=0;i<6;++i)
							printf("%x\n",localbuf[i]);
							FILE* tmpf=fopen("out.bin","wb");
							fwrite(localbuf,dat_siz,1,tmpf);
							fclose(tmpf);
						}
						cnt = caen::block_header::counter(localbuf);
						bt  = caen::block_header::timetag(localbuf);
						frs+=dat_siz;
						dat_siz /= sizeof(uint32_t);
						rn = 0;
						if(!is_start)
						{
							if(cnt==0) is_start=true;
							if(is_start==false)
							{
								dat_siz=0;
								return get_next_block();
							}
						}
						evt_siz=0;
					case 0x7:
						lch = -1;
						evt_siz += caen::block_header::size(localbuf+rn);
						brd     =  caen::block_header::bid(localbuf+rn);
					case 0x6:
						for(uint8_t i=lch+1;i<8;++i) if(((localbuf[rn+1]>>i)&1)==1){ ch=i; break; }
						rn += 6;
						is_eob=false;
						is_eod=false;
						return  true;
					case 0xf:
						if(verbose_level>1)
						{
							char tbuf[512-4*sizeof(uint32_t)];
							fread(tbuf,512-4*sizeof(uint32_t),1,fp);
							frs+=512-4*sizeof(uint32_t);
							printf("# ender info:\n");
							size_t offset[3]={64,128,256};
							for(auto off:offset)
							{
								char tmp[256];
								strncpy(tmp,tbuf+off-4*sizeof(uint32_t),off);
								remove_cr(tmp,off);
								printf("# %s\n",tmp);
							}
							printf("#\n");
						}
					default:
						is_eob=true;
//						printf("hflag invalid\n");
//						printf("0x%x rn=%d dat_siz=%d\n",hflag,rn,dat_siz);
						return false;
				}
			}
		public:
			typedef lazy_eval_t<annri> value_type;
			friend value_type;
			friend energy    ;
			friend time      ;
			friend channel   ;
			friend counter   ;
			friend board     ;
			friend pur       ;
			friend ttr       ;
			friend daq_id    ;
			friend readsize  ;
			friend timestamp ;
			friend extra_bits;
			friend unique_ch ;
			friend readnext  ;
			friend board_time;
			value_type value{this};
			void close(void)
			{
				if(fp) fclose(fp);
				fp=nullptr;
			}
			void verbose(uint32_t val)
			{
				verbose_level=(uint8_t)(val);
			}
			bool open(const char* fnm)
			{
				return open(fnm,verbose_level_silent);
			}
			bool open(const char* fnm,uint8_t mod)
			{
				close();
				fp=fopen(fnm,"rb");
				verbose_level=mod;
				if(!fp) return false;
				char tbuf[512];
				if(fread(tbuf,512,1,fp)!=1) return false;
				frs+=512;
				if((0xff&tbuf[3])!=0xf0)
				{
					if(verbose_level>0)
					{
						printf("Maybe, this file is not a valid raw data file\n");
						printf("Are you sure to continue analyzing this file?\n");
						printf("y/[n]");
						char c('n');
						scanf("%c",&c);
						if(c=='y') return true;
					}
					return false;
				}
				if(verbose_level>1)
				{
					printf("# header info:\n");
					size_t offset[3]={64,128,256};
					for(auto off:offset)
					{
						char tmp[256];
						strncpy(tmp,tbuf+off,off);
						remove_cr(tmp,off);
						printf("# %s\n",tmp);
					}
					printf("#\n");
				}
				return get_next_block();
			}
			annri()
			{
			}
			~annri()
			{
				close();
				free(localbuf);
			}
			template <typename Ad_>
			void register_adaptor(Ad_ a){}
			bool next(void)
			{
				is_eval=false;
				if(is_eob||is_eod)
				{
					if(!get_next_block()) return false;
				}
				rn+=2;
				if(rn==evt_siz) is_eob=true;
				if(rn>=dat_siz) is_eod=true;
				return true;
			}
			value_type& get(void)
			{
				return value;
			}
		};
		template <typename T>
		typename T::result_t get_v(lazy_eval_t<annri>& an)
		{
			return T::eval(an);
		}
	}
}} // namespace folklore::homerus;
