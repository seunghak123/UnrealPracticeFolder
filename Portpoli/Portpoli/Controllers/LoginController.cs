using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Portpoli.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class LoginController : Controller
    {
        private readonly UserDbContext _dbContext;
        public LoginController(UserDbContext dbContext)
        {
            _dbContext = dbContext;

        }

        [HttpPost(Name = "RequestToken")]
        public ActionResult<string> Post([FromForm] string userToken,[FromForm] int loginType)
        {
            //UserToken값 받아서 
            //loginType에 따라서 각 로그인 라이브러리를 통해 토큰 검증, 토큰 검증 성공하면
            //성공과 유저 유니크 아이디을 리턴하고
            //실패하면 실패 원인과 실패에러를 리턴한다
            

            //과정 
            //1-1. 유저가 디바이스(자동 로그인 기능) 에 저장된 유저 토큰값 검색 및 로그인 3번으로 이동
            //1-2. 유저 -> 라이브러리(플러그인) 로그인 요청
            //2. 라이브러리(플러그인)-> 유저에게 토큰 값 전달
            //3. 유저 -> 토큰 값가지고 서버에 로그인 요청
            //4. 서버가 토큰 값을 가지고 현재 로그인한 유저인지 확인 후 에러 또는 계정 데이터 전달
            //5. 신규 계정일 경우 새로운 기본 데이터 생성 후 저장(계정 토큰값, 플랫폼 타입 등등 디바이스 정보를 가지고) 

            #region 임시 코드    
            return Guid.NewGuid().ToString();
            #endregion 임시 코드
        }

    }
}
