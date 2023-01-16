import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { LoginModel } from 'src/app/conf/models';
import { AuthService } from 'src/app/srv/auth.service';
import { JwtService } from 'src/app/srv/jwt.service';

@Component({
  selector: 'app-login',
  template: `
    <h1>Login</h1>
    <input type="email" placeholder="email" [(ngModel)]="email"> <br>
    <input type="password" placeholder="password" [(ngModel)]="pass"> <br>
    <button (click)="login()">Submit</button>
  `
})
export class LoginComponent {

  email: string = ""
  pass: string = ""

  constructor(
    private authService: AuthService,
    private router: Router,
    private jwtService: JwtService
  ) { }

  login() {
    let data: LoginModel = {
      email: this.email,
      password: this.pass
    }

    this.authService.login(data)
    .subscribe({
      next: (res) => {
        console.log('Login Ok')
        if(res.body)
          this.onLoginSuccess(res.body)
      },
      error: (err) => { 
        console.log('Login Err') 
      }
    })
  }

  onLoginSuccess(jwt: string) {
    this.jwtService.setJwt(jwt)
    this.router.navigate(['profile'])
  }
}
