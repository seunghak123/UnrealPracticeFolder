﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace Portpoli.Models
{
    public class LoginViewModel
    {
        [Key]
        public string Id { get; set; }
        public string UserUUID { get; set; }
    }
}
