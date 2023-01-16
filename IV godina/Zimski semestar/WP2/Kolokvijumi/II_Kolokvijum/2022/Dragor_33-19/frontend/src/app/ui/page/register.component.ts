import { Component, Input } from '@angular/core';
import { RegisterModel } from 'src/app/conf/models';
import { AuthService } from 'src/app/srv/auth.service';

@Component({
  selector: 'app-register',
  template: `
    <h1>Register</h1>
    <input type="text" placeholder="name" [(ngModel)]="name"> <br>
    <input type="email" placeholder="email" [(ngModel)]="email"> <br>
    <input type="password" placeholder="password" [(ngModel)]="pass"> <br>
    <button (click)="register()">Submit</button>
  `
})
export class RegisterComponent {

  name: string = ''
  email: string = ''
  pass: string = ''

  constructor(
    private authService: AuthService,
  ) { }

  register() {
    let data: RegisterModel = {
      name: this.name,
      email: this.email,
      password: this.pass
    }

    this.authService.register(data)
    .subscribe({
      next: (res) => {
        this.onRegisterSuccess()
      },
      error: (err) => { 
        console.log('Register Error') 
      }
    })
  }

  onRegisterSuccess() {
    console.log('Register Ok')
  }

}
