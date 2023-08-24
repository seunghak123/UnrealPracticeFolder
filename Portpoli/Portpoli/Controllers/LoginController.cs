using Microsoft.AspNetCore.Mvc;
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
        [HttpGet]
        public ActionResult<string> Get([FromForm] string userToken,[FromForm] int loginType)
        {
            //UserToken값 받아서 
            //loginType에 따라서 각 로그인 라이브러리를 통해 토큰 검증, 토큰 검증 성공하면
            //성공과 유저 유니크 아이디을 리턴하고
            //실패하면 실패 원인과 실패에러를 리턴한다
            return "로그인 아이디";
        }

    }
}
